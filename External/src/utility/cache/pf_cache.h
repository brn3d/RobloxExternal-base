#pragma once
#include "../../utility/cache/sdk.h"
#include <vector>
#include <string>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <chrono>

namespace PfCache
{
    inline constexpr std::uint64_t kPlaceId = 292439477ull;

    inline constexpr std::uintptr_t kTextLabelText = 0xBA0;
    inline constexpr std::uintptr_t kTextLabelTextColor3 = 0xEB8;
    inline constexpr std::uintptr_t kGuiObjectSize = 0x520;

    struct Color3
    {
        float r = 0.0f, g = 0.0f, b = 0.0f;
    };

    struct Udim
    {
        float scale = 0.0f;
        int offset = 0;
    };

    struct Udim2
    {
        Udim x{};
        Udim y{};
    };

    struct PfPlayer
    {
        std::uintptr_t modelAddr = 0;
        std::uintptr_t teamFolderAddr = 0;
        std::uintptr_t headAddr = 0;
        std::uintptr_t torsoAddr = 0;
        std::uintptr_t labelAddr = 0;
        std::uintptr_t healthBarAddr = 0;
        std::uintptr_t headPrim = 0;
        std::uintptr_t torsoPrim = 0;
        std::vector<std::uintptr_t> limbAddrs;
        std::string name;
        float health = 1.0f;
        bool isEnemy = true;
        bool colorValid = false;
        bool isValid = false;
    };

    inline std::vector<PfPlayer> players;
    inline std::uintptr_t localCharacterAddr = 0;
    inline std::uintptr_t localTeamFolderAddr = 0;
    inline std::uintptr_t workspacePlayersAddr = 0;
    inline thenwefuckin::math::vec3 localPos{};

    struct PfDebug
    {
        std::uint64_t placeIdRead = 0;
        int wsChildren = -1;
        int teamFolders = 0;
        int modelsScanned = 0;
        int modelsKept = 0;
        int modelsNoHeadTorso = 0;
        int modelsEmptyName = 0;
        int hpFrames = 0;
        int hpZero = 0;
        int hpAllZeroFix = 0;
        int enemies = 0;
        float hpSample = -1.0f;
        const char* failStage = "not run";
    };
    inline PfDebug dbg;
    inline std::chrono::steady_clock::time_point lastFull{};

    inline std::uint64_t ReadPlaceId()
    {
        if (!thenwefuckin::g_ctx.datamodel.addr)
            return 0;
        return thenwefuckin::g_proc->read<std::uint64_t>(
            thenwefuckin::g_ctx.datamodel.addr + Offsets::DataModel::PlaceId);
    }

    inline bool IsActivePlace()
    {
        return ReadPlaceId() == kPlaceId;
    }

    inline bool LooksLikePf(std::uintptr_t wsPlayers)
    {
        if (!wsPlayers || !thenwefuckin::g_proc)
            return false;
        thenwefuckin::node ws{ wsPlayers };
        for (auto& folder : ws.children())
        {
            if (folder.class_name() != "Folder")
                continue;
            for (auto& model : folder.children())
            {
                if (model.class_name() != "Model")
                    continue;
                for (auto& part : model.children())
                {
                    const std::string pc = part.class_name();
                    if (pc != "Part" && pc != "MeshPart")
                        continue;
                    for (auto& c : part.children())
                    {
                        if (c.class_name() == "BillboardGui")
                            return true;
                    }
                }
            }
        }
        return false;
    }

    inline std::uintptr_t FindWorkspacePlayersFolder()
    {
        if (!thenwefuckin::g_ctx.workspace.addr)
            return 0;
        for (auto& c : thenwefuckin::g_ctx.workspace.children())
        {
            if (c.class_name() == "Folder" && c.name() == "Players")
                return c.addr;
        }
        return 0;
    }

    inline std::string ReadLabelText(std::uintptr_t labelAddr)
    {
        if (!labelAddr || !thenwefuckin::g_proc)
            return {};
        return thenwefuckin::g_proc->read_game_string(labelAddr + kTextLabelText);
    }

    inline bool ReadLabelColor(std::uintptr_t labelAddr, Color3& out)
    {
        if (!labelAddr || !thenwefuckin::g_proc)
            return false;
        out = thenwefuckin::g_proc->read<Color3>(labelAddr + kTextLabelTextColor3);
        if (!std::isfinite(out.r) || !std::isfinite(out.g) || !std::isfinite(out.b))
            return false;
        if (out.r < 0.0f || out.r > 1.0f || out.g < 0.0f || out.g > 1.0f || out.b < 0.0f || out.b > 1.0f)
            return false;
        return true;
    }

    inline bool IsEnemyLabelColor(const Color3& c)
    {
        const int r = (int)(c.r * 255.0f + 0.5f);
        const int g = (int)(c.g * 255.0f + 0.5f);
        const int b = (int)(c.b * 255.0f + 0.5f);
        return std::abs(r - 255) <= 8 && std::abs(g - 10) <= 12 && std::abs(b - 20) <= 12;
    }

    inline std::uintptr_t FindBillboardLabel(std::uintptr_t modelAddr)
    {
        thenwefuckin::node model{ modelAddr };
        for (auto& part : model.children())
        {
            const std::string pc = part.class_name();
            if (pc != "Part" && pc != "MeshPart")
                continue;
            for (auto& c : part.children())
            {
                if (c.class_name() != "BillboardGui")
                    continue;
                for (auto& bc : c.children())
                {
                    if (bc.class_name() == "TextLabel")
                        return bc.addr;
                }
            }
        }
        return 0;
    }

    inline std::string ReadModelName(std::uintptr_t modelAddr)
    {
        const auto label = FindBillboardLabel(modelAddr);
        if (label)
            return ReadLabelText(label);
        return {};
    }

    inline std::uintptr_t FindHealthPercent(std::uintptr_t modelAddr)
    {
        thenwefuckin::node model{ modelAddr };
        for (auto& part : model.children())
        {
            const std::string pc = part.class_name();
            if (pc != "Part" && pc != "MeshPart")
                continue;
            for (auto& c : part.children())
            {
                if (c.class_name() != "BillboardGui")
                    continue;
                for (auto& bc : c.children())
                {
                    if (bc.class_name() != "TextLabel")
                        continue;
                    for (auto& f : bc.children())
                    {
                        if (f.class_name() != "Frame" || f.name() != "Health")
                            continue;
                        for (auto& pf : f.children())
                        {
                            if (pf.class_name() == "Frame" && pf.name() == "Percent")
                                return pf.addr;
                        }
                    }
                }
            }
        }
        return 0;
    }

    inline float ReadHealthFrac(std::uintptr_t percentAddr)
    {
        if (!percentAddr || !thenwefuckin::g_proc)
            return 1.0f;
        const auto sz = thenwefuckin::g_proc->read<Udim2>(percentAddr + kGuiObjectSize);
        float f = sz.x.scale;
        if (!std::isfinite(f) || f < 0.0f || f > 1.0f)
            return 1.0f;
        return f;
    }

    inline std::vector<std::uintptr_t> CollectLimbs(std::uintptr_t modelAddr, std::uintptr_t head, std::uintptr_t torso)
    {
        std::vector<std::uintptr_t> out;
        thenwefuckin::node model{ modelAddr };
        for (auto& part : model.children())
        {
            const std::string pc = part.class_name();
            if (pc != "Part" && pc != "MeshPart")
                continue;
            if (part.addr == head || part.addr == torso)
                continue;
            out.push_back(part.addr);
        }
        return out;
    }

    inline void ResolveCharacter(std::uintptr_t modelAddr, std::uintptr_t& outHead, std::uintptr_t& outTorso)
    {
        outHead = 0;
        outTorso = 0;
        thenwefuckin::node model{ modelAddr };
        for (auto& part : model.children())
        {
            const std::string pc = part.class_name();
            if (pc != "Part" && pc != "MeshPart")
                continue;
            bool isHead = false;
            bool isTorso = false;
            for (auto& c : part.children())
            {
                const std::string cc = c.class_name();
                if (cc == "BillboardGui")
                {
                    isHead = true;
                    break;
                }
                if (cc == "SpotLight")
                {
                    isTorso = true;
                    break;
                }
            }
            if (isHead && !outHead)
                outHead = part.addr;
            else if (isTorso && !outTorso)
                outTorso = part.addr;
        }
    }

    inline std::uintptr_t ResolveLocalCharacter(std::uintptr_t wsPlayers)
    {
        using namespace thenwefuckin;
        if (g_ctx.local_player.addr && g_proc)
        {
            const auto mi = g_proc->read<std::uintptr_t>(
                g_ctx.local_player.addr + Offsets::Player::ModelInstance);
            if (mi)
            {
                node parent{ g_proc->read<std::uintptr_t>(mi + Offsets::Instance::Parent) };
                if (parent.addr && parent.class_name() == "Folder")
                {
                    node grand{ g_proc->read<std::uintptr_t>(parent.addr + Offsets::Instance::Parent) };
                    if (grand.addr == wsPlayers)
                        return mi;
                }
                return mi;
            }
        }
        return 0;
    }

    inline int ScoreFolderEnemy(std::uintptr_t folderAddr)
    {
        int enemy = 0;
        int friendly = 0;
        thenwefuckin::node folder{ folderAddr };
        for (auto& model : folder.children())
        {
            if (model.class_name() != "Model")
                continue;
            const auto label = FindBillboardLabel(model.addr);
            Color3 col{};
            if (!ReadLabelColor(label, col))
                continue;
            if (IsEnemyLabelColor(col))
                ++enemy;
            else
                ++friendly;
        }
        return enemy - friendly;
    }

    inline bool IsTeammate(const PfPlayer& p)
    {
        if (p.colorValid)
            return !p.isEnemy;
        if (localTeamFolderAddr && p.teamFolderAddr)
            return p.teamFolderAddr == localTeamFolderAddr;
        return false;
    }

    inline void RefreshFast()
    {
        using namespace thenwefuckin;
        if (g_ctx.camera.addr && g_proc)
            localPos = g_proc->read<math::vec3>(g_ctx.camera.addr + Offsets::Camera::Position);
        int zeros = 0;
        for (auto& p : players)
        {
            if (!p.isValid)
                continue;
            if (p.healthBarAddr)
                p.health = ReadHealthFrac(p.healthBarAddr);
            if (p.health <= 0.0f)
                ++zeros;
        }
        if (!players.empty() && zeros == (int)players.size())
        {
            for (auto& p : players)
                p.health = 1.0f;
            dbg.hpAllZeroFix = 1;
        }
    }

    inline void update()
    {
        using namespace thenwefuckin;
        const auto now = std::chrono::steady_clock::now();
        if (lastFull != std::chrono::steady_clock::time_point{} &&
            std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFull).count() < 100)
        {
            RefreshFast();
            return;
        }
        lastFull = now;

        players.clear();
        localCharacterAddr = 0;
        localTeamFolderAddr = 0;
        workspacePlayersAddr = 0;
        dbg = PfDebug{};

        dbg.placeIdRead = ReadPlaceId();
        if (!g_ctx.workspace.addr)
        {
            dbg.failStage = "no workspace";
            return;
        }

        const auto wsPlayers = FindWorkspacePlayersFolder();
        if (!wsPlayers)
        {
            dbg.failStage = "no Workspace.Players folder";
            return;
        }
        workspacePlayersAddr = wsPlayers;

        if (dbg.placeIdRead != kPlaceId && !LooksLikePf(wsPlayers))
        {
            dbg.failStage = "placeid mismatch + no pf structure";
            return;
        }

        std::string localName;
        if (g_ctx.local_player.addr)
            localName = g_ctx.local_player.name();
        localCharacterAddr = ResolveLocalCharacter(wsPlayers);

        dbg.wsChildren = (int)node{ wsPlayers }.children().size();

        std::uintptr_t folders[2]{};
        int nf = 0;
        node ws{ wsPlayers };
        for (auto& folder : ws.children())
        {
            if (folder.class_name() != "Folder")
                continue;
            if (nf < 2)
                folders[nf++] = folder.addr;
            dbg.teamFolders++;
        }
        if (nf == 2)
        {
            const int s0 = ScoreFolderEnemy(folders[0]);
            const int s1 = ScoreFolderEnemy(folders[1]);
            if (s0 > 0 && s1 <= 0)
                localTeamFolderAddr = folders[1];
            else if (s1 > 0 && s0 <= 0)
                localTeamFolderAddr = folders[0];
            else if (s0 < 0 && s1 >= 0)
                localTeamFolderAddr = folders[0];
            else if (s1 < 0 && s0 >= 0)
                localTeamFolderAddr = folders[1];
        }
        if (!localTeamFolderAddr && localCharacterAddr && g_proc)
        {
            node parent{ g_proc->read<std::uintptr_t>(localCharacterAddr + Offsets::Instance::Parent) };
            node grand{ parent.addr ? g_proc->read<std::uintptr_t>(parent.addr + Offsets::Instance::Parent) : 0 };
            if (grand.addr == wsPlayers)
                localTeamFolderAddr = parent.addr;
        }

        for (auto& folder : ws.children())
        {
            if (folder.class_name() != "Folder")
                continue;
            for (auto& model : folder.children())
            {
                if (model.class_name() != "Model")
                    continue;
                dbg.modelsScanned++;
                if (model.addr == localCharacterAddr)
                    continue;

                std::uintptr_t head = 0, torso = 0;
                ResolveCharacter(model.addr, head, torso);
                if (!head && !torso)
                {
                    dbg.modelsNoHeadTorso++;
                    continue;
                }

                const auto label = FindBillboardLabel(model.addr);
                Color3 col{};
                const bool colOk = ReadLabelColor(label, col);
                const auto percent = FindHealthPercent(model.addr);
                const float hp = ReadHealthFrac(percent);
                if (percent)
                    dbg.hpFrames++;
                if (hp <= 0.0f)
                    dbg.hpZero++;
                if (dbg.hpSample < 0.0f && percent)
                    dbg.hpSample = hp;
                if (percent && hp <= 0.0f)
                    continue;

                PfPlayer p{};
                p.modelAddr = model.addr;
                p.teamFolderAddr = folder.addr;
                p.headAddr = head;
                p.torsoAddr = torso;

                if (head)
                    p.headPrim = thenwefuckin::node{ head }.primitive();
                if (torso)
                    p.torsoPrim = thenwefuckin::node{ torso }.primitive();
                p.labelAddr = label;
                p.healthBarAddr = percent;
                p.limbAddrs = CollectLimbs(model.addr, head, torso);
                p.health = hp;
                p.colorValid = colOk;
                p.isEnemy = colOk ? IsEnemyLabelColor(col) : true;
                if (p.isEnemy)
                    dbg.enemies++;
                p.name = ReadModelName(model.addr);
                if (p.name.empty())
                    p.name = model.name();
                if (p.name.empty())
                {
                    dbg.modelsEmptyName++;
                    char buf[32];
                    std::snprintf(buf, sizeof(buf), "pf_%llx", (unsigned long long)model.addr);
                    p.name = buf;
                }
                if (!localName.empty() && p.name == localName)
                    continue;
                p.isValid = true;
                players.push_back(std::move(p));
                dbg.modelsKept++;
            }
        }

        int zeros = 0;
        for (auto& p : players)
        {
            if (p.health <= 0.0f)
                ++zeros;
        }
        if (!players.empty() && zeros == (int)players.size())
        {
            for (auto& p : players)
                p.health = 1.0f;
            dbg.hpAllZeroFix = 1;
        }

        dbg.failStage = players.empty() ? "ok but empty" : "ok";

        if (g_ctx.camera.addr && g_proc)
            localPos = g_proc->read<math::vec3>(g_ctx.camera.addr + Offsets::Camera::Position);
    }
}
