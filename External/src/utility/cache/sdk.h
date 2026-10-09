#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <atomic>
#include <cstdint>
#include <cmath>
#include <chrono>
#include <string>
#include <vector>
#include <memory>

#include "math.h"
#include "../struct/offsets.h"
#include "../struct/structs.h"
#include "../struct/world2screen.h"
#include "../memory/syscall.h"

namespace thenwefuckin
{
    class process
    {
    public:
        process() = default;
        ~process() { detach(); }

        process(const process&) = delete;
        process& operator=(const process&) = delete;

        bool attach(const std::string& exe_name)
        {
            uint32_t pid = find_pid(exe_name);
            if (!pid)
                return false;

            HANDLE h = OpenProcess(
                PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION,
                FALSE, pid);
            if (!h || h == INVALID_HANDLE_VALUE)
                return false;

            detach();
            handle = h;
            pid_ = pid;
            base_ = find_module(exe_name);
            return base_ != 0;
        }

        void detach()
        {
            if (handle && handle != INVALID_HANDLE_VALUE)
                CloseHandle(handle);
            handle = nullptr;
            pid_ = 0;
            base_ = 0;
        }

        bool connected() const { return handle && handle != INVALID_HANDLE_VALUE; }
        bool alive() const
        {
            if (!connected())
                return false;
            DWORD code = 0;
            if (!GetExitCodeProcess(handle, &code))
                return false;
            return code == STILL_ACTIVE;
        }
        uint64_t base() const { return base_; }
        uint32_t pid() const { return pid_; }
        HANDLE raw() const { return handle; }

        template <typename T>
        T read(uint64_t addr) const
        {
            T v{};
            if (!connected())
                return v;
#ifdef _M_X64
            if (syscalls::ready())
            {
                unsigned long long done = 0;
                long st = Rax_ReadVirtualMemory(handle, reinterpret_cast<LPCVOID>(addr), &v, sizeof(T), &done);
                if (st < 0 || done != sizeof(T))
                    v = T{};
                return v;
            }
#endif
            ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(addr), &v, sizeof(T), nullptr);
            return v;
        }

        template <typename T>
        void write(uint64_t addr, const T& v) const
        {
            if (!connected())
                return;
#ifdef _M_X64
            if (syscalls::ready())
            {
                unsigned long long done = 0;
                Rax_WriteVirtualMemory(handle, reinterpret_cast<LPVOID>(addr), &v, sizeof(T), &done);
                return;
            }
#endif
            WriteProcessMemory(handle, reinterpret_cast<LPVOID>(addr), &v, sizeof(T), nullptr);
        }

        bool read_buf(uint64_t addr, void* dst, size_t size) const
        {
            if (!connected() || !dst || !size)
                return false;
#ifdef _M_X64
            if (syscalls::ready())
            {
                unsigned long long done = 0;
                long st = Rax_ReadVirtualMemory(handle, reinterpret_cast<LPCVOID>(addr), dst, size, &done);
                return st >= 0 && done == size;
            }
#endif
            SIZE_T done = 0;
            return ReadProcessMemory(handle, reinterpret_cast<LPCVOID>(addr), dst, size, &done) && done == size;
        }

        bool write_buf(uint64_t addr, const void* src, size_t size) const
        {
            if (!connected() || !src || !size)
                return false;
#ifdef _M_X64
            if (syscalls::ready())
            {
                unsigned long long done = 0;
                long st = Rax_WriteVirtualMemory(handle, reinterpret_cast<LPVOID>(addr), src, size, &done);
                return st >= 0 && done == size;
            }
#endif
            SIZE_T done = 0;
            return WriteProcessMemory(handle, reinterpret_cast<LPVOID>(addr), src, size, &done) && done == size;
        }

        std::string read_game_string(uint64_t addr) const
        {
            if (!addr || !connected())
                return {};
            int32_t len = read<int32_t>(addr + 0x10);
            if (len <= 0 || len > 256)
                return {};
            uint64_t ptr = (len >= 16) ? read<uint64_t>(addr) : addr;
            if (!ptr)
                return {};
            std::vector<char> buf(static_cast<size_t>(len) + 1, 0);
            if (!read_buf(ptr, buf.data(), static_cast<size_t>(len)))
                return {};
            return std::string(buf.data(), static_cast<size_t>(len));
        }

        void write_game_string(uint64_t addr, const std::string& value) const
        {
            if (!addr || !connected())
                return;
            uint64_t cap = read<uint64_t>(addr + 0x18);
            uint64_t len = static_cast<uint64_t>(value.size());
            if (len > cap)
            {
                void* mem = VirtualAllocEx(handle, nullptr, len + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                if (!mem)
                    return;
                uint64_t dst = reinterpret_cast<uint64_t>(mem);
                write_buf(dst, value.data(), value.size());
                write<char>(dst + len, '\0');
                write<uint64_t>(addr, dst);
                write<uint64_t>(addr + 0x10, len);
                write<uint64_t>(addr + 0x18, len);
                return;
            }
            uint64_t dst = cap >= 16 ? read<uint64_t>(addr) : addr;
            if (!dst)
                return;
            if (!value.empty())
                write_buf(dst, value.data(), value.size());
            write<char>(dst + len, '\0');
            write<uint64_t>(addr + 0x10, len);
        }

    private:
        uint32_t find_pid(const std::string& exe_name)
        {
            HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            if (snap == INVALID_HANDLE_VALUE)
                return 0;

            PROCESSENTRY32 entry{};
            entry.dwSize = sizeof(entry);
            uint32_t found = 0;

            if (Process32First(snap, &entry))
            {
                do
                {
                    char exeA[MAX_PATH]{};
                    WideCharToMultiByte(CP_UTF8, 0, entry.szExeFile, -1, exeA, MAX_PATH, nullptr, nullptr);
                    if (_stricmp(exeA, exe_name.c_str()) == 0)
                    {
                        found = entry.th32ProcessID;
                        break;
                    }
                } while (Process32Next(snap, &entry));
            }
            CloseHandle(snap);
            return found;
        }

        uint64_t find_module(const std::string& exe_name)
        {
            if (!connected())
                return 0;
            HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid_);
            if (snap == INVALID_HANDLE_VALUE)
                return 0;

            MODULEENTRY32 entry{};
            entry.dwSize = sizeof(entry);
            uint64_t found = 0;

            if (Module32First(snap, &entry))
            {
                do
                {
                    char modA[MAX_PATH]{};
                    WideCharToMultiByte(CP_UTF8, 0, entry.szModule, -1, modA, MAX_PATH, nullptr, nullptr);
                    if (_stricmp(modA, exe_name.c_str()) == 0)
                    {
                        found = reinterpret_cast<uint64_t>(entry.modBaseAddr);
                        break;
                    }
                } while (Module32Next(snap, &entry));
            }
            CloseHandle(snap);
            return found;
        }

        HANDLE handle = nullptr;
        uint32_t pid_ = 0;
        uint64_t base_ = 0;
    };

    inline std::shared_ptr<process> g_proc = std::make_shared<process>();

    class node
    {
    public:
        uintptr_t addr = 0;

        node() = default;
        explicit node(uintptr_t a) : addr(a) {}
        explicit operator bool() const { return addr != 0; }

        std::string name() const
        {
            if (!addr)
                return {};
            uintptr_t container = g_proc->read<uintptr_t>(addr + Offsets::Instance::NameContainer);
            if (!container)
                return {};
            return g_proc->read_game_string(container + Offsets::Instance::Name);
        }

        std::string class_name() const
        {
            if (!addr)
                return {};
            uintptr_t desc = g_proc->read<uintptr_t>(addr + Offsets::Instance::ClassDescriptor);
            if (!desc)
                return {};
            uintptr_t ptr = g_proc->read<uintptr_t>(desc + Offsets::Instance::ClassName);
            return ptr ? g_proc->read_game_string(ptr) : std::string{};
        }

        node parent() const
        {
            return addr ? node(g_proc->read<uintptr_t>(addr + Offsets::Instance::Parent)) : node{};
        }

        std::vector<node> children() const
        {
            std::vector<node> out;
            if (!addr)
                return out;

            uintptr_t list = g_proc->read<uintptr_t>(addr + Offsets::Instance::ChildrenStart);
            if (!list)
                return out;

            uintptr_t end = g_proc->read<uintptr_t>(list + Offsets::Instance::ChildrenEnd);
            uintptr_t cur = g_proc->read<uintptr_t>(list);
            if (!cur || !end || end < cur)
                return out;

            size_t count = (size_t)(end - cur) / 0x10;
            if (count > 2048)
                count = 2048;
            if (!count)
                return out;
            size_t bytes = count * 0x10;
            if (bytes > 0x10000)
                return out;
            std::vector<uint8_t> buf(bytes);
            if (!g_proc->read_buf(cur, buf.data(), bytes))
                return out;

            out.reserve(count < 32 ? count : 32);
            const uintptr_t* w = (const uintptr_t*)buf.data();
            for (size_t n = 0; n < count * 2; n += 2)
            {
                if (w[n])
                    out.emplace_back(w[n]);
            }
            return out;
        }

        node find_child(const std::string& wanted) const
        {
            for (auto& c : children())
            {
                if (c.name() == wanted)
                    return c;
            }
            return {};
        }

        node find_child_of_class(const std::string& cls) const
        {
            for (auto& c : children())
            {
                if (c.class_name() == cls)
                    return c;
            }
            return {};
        }

        uintptr_t primitive() const
        {
            return addr ? g_proc->read<uintptr_t>(addr + Offsets::BasePart::Primitive) : 0;
        }

        math::vec3 position() const
        {
            uintptr_t prim = primitive();
            return prim ? g_proc->read<math::vec3>(prim + Offsets::Primitive::Position) : math::vec3{};
        }

        math::vec3 velocity() const
        {
            uintptr_t prim = primitive();
            return prim ? g_proc->read<math::vec3>(prim + Offsets::Primitive::AssemblyLinearVelocity) : math::vec3{};
        }

        math::frame cframe() const
        {
            uintptr_t prim = primitive();
            return prim ? g_proc->read<math::frame>(prim + Offsets::Primitive::Rotation) : math::frame{};
        }

        float distance_to(const math::vec3& p) const
        {
            return position().dist_to(p);
        }
    };

    inline node find_live_humanoid(const node& character, float* outHp = nullptr, float* outMaxHp = nullptr)
    {
        node fallback{};
        float fallbackHp = 0.0f, fallbackMax = 0.0f;
        node best{};
        float bestHp = 0.0f, bestMax = 0.0f;
        float bestFrac = 2.0f;
        if (character && g_proc)
        {
            for (auto& c : character.children())
            {
                if (c.class_name() != "Humanoid")
                    continue;
                float hp = g_proc->read<float>(c.addr + Offsets::Humanoid::Health);
                float mx = g_proc->read<float>(c.addr + Offsets::Humanoid::MaxHealth);
                if (!fallback)
                {
                    fallback = c;
                    fallbackHp = hp;
                    fallbackMax = mx;
                }
                if (mx > 0.0f && hp > 0.0f)
                {
                    float frac = hp / mx;
                    if (frac < bestFrac)
                    {
                        bestFrac = frac;
                        best = c;
                        bestHp = hp;
                        bestMax = mx;
                    }
                }
            }
        }
        node pick = best ? best : fallback;
        if (outHp) *outHp = best ? bestHp : fallbackHp;
        if (outMaxHp) *outMaxHp = best ? bestMax : fallbackMax;
        return pick;
    }

    struct context
    {
        node datamodel;
        node workspace;
        node players;
        node local_player;
        node camera;
        node local_root;

        node local_humanoid;
        math::view_matrix view{};
        math::vec3 local_pos{};
        math::vec3 local_velocity{};
        bool ready = false;

        math::vec3 m_lastPos{};
        std::chrono::steady_clock::time_point m_lastSample{};
        bool m_haveSample = false;

        node m_cachedChar{};

        node get_character(const node& player_node) const
        {
            if (!player_node)
                return node{};

            uintptr_t charAddr = g_proc->read<uintptr_t>(player_node.addr + Offsets::Player::ModelInstance);
            if (charAddr)
            {
                node c{ charAddr };
                if (c.addr && (c.find_child_of_class("Humanoid") || c.find_child("Head") || c.find_child("HumanoidRootPart") || c.primitive()))
                    return c;
            }

            std::string name = player_node.name();
            if (name.empty() || !workspace)
                return node{};

            node direct = workspace.find_child(name);
            if (direct && (direct.find_child_of_class("Humanoid") || direct.find_child("Head") || direct.find_child("HumanoidRootPart")))
                return direct;

            static const char* const kFolderNames[] = {
                "PLAYERS", "Players", "Characters", "characters",
                "Entities", "entities", "Actors", "actors", "Units"
            };
            for (const char* fn : kFolderNames)
            {
                node folder = workspace.find_child(fn);
                if (folder)
                {
                    node inside = folder.find_child(name);
                    if (inside && (inside.find_child_of_class("Humanoid") || inside.find_child("Head") || inside.find_child("HumanoidRootPart")))
                        return inside;
                }
            }

            return node{};
        }

        bool resolve_services(uint64_t dmAddr)
        {
            datamodel = node(dmAddr);
            if (!datamodel)
                return false;

            workspace = node(g_proc->read<uintptr_t>(datamodel.addr + Offsets::DataModel::Workspace));
            if (!workspace)
                workspace = datamodel.find_child_of_class("Workspace");
            if (!workspace)
                workspace = datamodel.find_child("Workspace");

            players = datamodel.find_child_of_class("Players");
            if (!players)
                players = datamodel.find_child("Players");
            if (!players)
                players = datamodel.find_child("PlayerService");
            if (!players)
                return false;

            local_player = node(g_proc->read<uintptr_t>(players.addr + Offsets::Players::LocalPlayer));
            if (!local_player)
            {
                for (auto& p : players.children())
                {
                    if (p.find_child_of_class("PlayerScripts") || p.find_child_of_class("PlayerGui"))
                    {
                        local_player = p;
                        break;
                    }
                }
            }

            uintptr_t curCam = workspace ? g_proc->read<uintptr_t>(workspace.addr + Offsets::Workspace::CurrentCamera) : 0;
            camera = curCam ? node{ curCam } : (workspace ? workspace.find_child_of_class("Camera") : node{});

            local_root = node{};
            local_humanoid = node{};
            m_cachedChar = node{};
            if (local_player)
            {
                node character = get_character(local_player);
                if (character)
                {
                    m_cachedChar = character;
                    local_root = character.find_child("HumanoidRootPart");
                    if (!local_root) local_root = character.find_child("Torso");
                    if (!local_root) local_root = character.find_child("UpperTorso");
                    if (!local_root) local_root = character.find_child("Head");
                    local_humanoid = find_live_humanoid(character);
                }
            }

            m_cachedDm = dmAddr;
            return true;
        }

        bool refresh()
        {
            local_velocity = math::vec3{};
            m_haveSample = false;
            if (!g_proc->connected())
            {
                ready = false;
                m_cachedDm = 0;
                m_cachedChar = node{};
                return false;
            }

            uint64_t fake = g_proc->read<uint64_t>(g_proc->base() + Offsets::FakeDataModel::Pointer);
            if (!fake)
            {
                ready = false;
                m_cachedDm = 0;
                m_cachedChar = node{};
                return false;
            }
            uint64_t dmAddr = g_proc->read<uintptr_t>(fake + Offsets::FakeDataModel::RealDataModel);

            auto now = std::chrono::steady_clock::now();
            bool cacheValid = (dmAddr != 0 && dmAddr == m_cachedDm && datamodel && players);
            bool cacheStale = cacheValid &&
                std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastResolve).count() >= 250;

            if (!cacheValid || cacheStale)
            {
                m_lastResolve = now;
                if (!resolve_services(dmAddr))
                {
                    ready = false;
                    m_cachedDm = 0;
                    m_cachedChar = node{};
                    return false;
                }
            }

            uint64_t visual = g_proc->read<uint64_t>(g_proc->base() + Offsets::VisualEngine::Pointer);
            if (visual)
                view = g_proc->read<math::view_matrix>(visual + Offsets::VisualEngine::ViewMatrix);

            if (workspace)
            {
                uintptr_t curCam = g_proc->read<uintptr_t>(workspace.addr + Offsets::Workspace::CurrentCamera);
                if (curCam)
                    camera = node{ curCam };
                else if (!camera)
                    camera = workspace.find_child_of_class("Camera");
            }

            if (local_player)
            {
                node character = get_character(local_player);
                if (character.addr != m_cachedChar.addr || !local_root || !local_root.primitive())
                {
                    m_cachedChar = character;
                    if (character)
                    {
                        local_root = character.find_child("HumanoidRootPart");
                        if (!local_root) local_root = character.find_child("Torso");
                        if (!local_root) local_root = character.find_child("UpperTorso");
                        if (!local_root) local_root = character.find_child("Head");
                        local_humanoid = find_live_humanoid(character);
                    }
                    else
                    {
                        local_root = node{};
                        local_humanoid = node{};
                    }
                }
            }

            if (local_root)
            {
                local_pos = local_root.position();
                local_velocity = sample_velocity(local_root);
            }

            ready = (workspace && players && local_player);
            return ready;
        }

        node resolve_local_humanoid() const
        {
            if (!g_proc || !g_proc->connected() || !local_player)
                return {};
            node character = get_character(local_player);
            if (!character)
                return {};
            return find_live_humanoid(character);
        }

        node resolve_camera() const
        {
            if (!g_proc || !g_proc->connected())
                return {};
            if (workspace)
            {
                uintptr_t curCam = g_proc->read<uintptr_t>(workspace.addr + Offsets::Workspace::CurrentCamera);
                if (curCam)
                    return node{ curCam };
            }
            return camera;
        }

        uint64_t m_cachedDm = 0;
        std::chrono::steady_clock::time_point m_lastResolve{};

        math::vec3 sample_velocity(const node& root)
        {
            math::vec3 v = root.velocity();

            bool sane = std::isfinite(v.x) && std::isfinite(v.y) && std::isfinite(v.z)
                        && v.length() < 5000.0f;
            if (sane)
                return v;

            auto now = std::chrono::steady_clock::now();
            if (m_haveSample && now > m_lastSample)
            {
                float dt = std::chrono::duration<float>(now - m_lastSample).count();
                if (dt > 0.0005f && dt < 0.5f)
                    v = (local_pos - m_lastPos) / dt;
            }
            m_lastPos = local_pos;
            m_lastSample = now;
            m_haveSample = true;
            return v;
        }

        std::vector<node> player_list() const
        {
            if (!players)
                return {};
            return players.children();
        }
    };

    inline context g_ctx;
}
