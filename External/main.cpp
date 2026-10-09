#define STB_IMAGE_IMPLEMENTATION
#include "src/utility/stb/stb_image.h"
#include "src/menu/core/overlay/overlay.h"
#include "src/menu/core/gui/menu.h"
#include "src/menu/overlay/settings.h"
#include "src/utility/cache/sdk.h"
#include "src/utility/logger/logger.h"
#include "src/utility/struct/offsets.h"
#include "src/features/visual/core/visual.h"
#include "src/features/aim/core/aim.h"
#include "src/features/aim/viewport/viewport.h"
#include "src/features/aim/raycast/raycast.h"
#include "src/features/aim/wraith/wraith.h"
#include "src/utility/cache/pf_cache.h"
#include "src/features/misc/core/misc.h"
#include "src/features/misc/freecam/freecam.h"
#include "src/utility/global/globals.h"
#include <Windows.h>
#include <shellapi.h>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <csignal>
#include <exception>
#include <iostream>
#include <thread>

bool g_menuOpen = false;
bool g_vsync = false;
bool g_streamProof = false;
int g_fpsCap = 0;
float g_localSpeed = -1.0f;

static void PrintDebugLines(float fps)
{
    using namespace thenwefuckin;
    bool conn = g_proc && g_proc->connected();
    uint32_t pid = conn ? g_proc->pid() : 0;
    uint64_t base = conn ? g_proc->base() : 0;
    uint64_t dm = g_ctx.datamodel ? g_ctx.datamodel.addr : 0;
    uint64_t ws = g_ctx.workspace ? g_ctx.workspace.addr : 0;
    uint64_t pl = g_ctx.players ? g_ctx.players.addr : 0;
    std::string plName = g_ctx.players ? g_ctx.players.name() : "none";
    std::string lpName = g_ctx.local_player ? g_ctx.local_player.name() : "none";
    size_t plCount = g_ctx.player_list().size();
    math::vec3 pos = g_ctx.local_pos;

    LOGF("debug", "FPS: %5.1f | PID: %u Base: 0x%llX | DM: 0x%llX WS: 0x%llX | Players(%s): %zu (0x%llX) | Local: %s | Pos: (%.1f, %.1f, %.1f) Speed: %.1f | Ready: %d",
        fps, pid, (unsigned long long)base, (unsigned long long)dm, (unsigned long long)ws,
        plName.c_str(), plCount, (unsigned long long)pl,
        lpName.c_str(), pos.x, pos.y, pos.z, g_localSpeed, g_ctx.ready ? 1 : 0);
}

ID3D11ShaderResourceView* Menu::LoadIconTexture(const unsigned char* png, int len)
{
    int tw = 0;
    int th = 0;
    unsigned char* px = stbi_load_from_memory(png, len, &tw, &th, nullptr, 4);
    if (!px || tw <= 0 || th <= 0)
    {
        if (px) stbi_image_free(px);
        return nullptr;
    }
    ID3D11ShaderResourceView* srv = nullptr;
    ID3D11Device* dev = Overlay::GetDeviceStatic();
    if (dev)
    {
        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = (UINT)tw;
        desc.Height = (UINT)th;
        desc.MipLevels = 1;
        desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        D3D11_SUBRESOURCE_DATA init = {};
        init.pSysMem = px;
        init.SysMemPitch = (UINT)(tw * 4);
        ID3D11Texture2D* tex = nullptr;
        if (SUCCEEDED(dev->CreateTexture2D(&desc, &init, &tex)))
        {
            dev->CreateShaderResourceView(tex, nullptr, &srv);
            tex->Release();
        }
    }
    stbi_image_free(px);
    return srv;
}

static bool NeedsGameData()
{
    using namespace thenwefuckin;
    return settings::aim_enabled
        || settings::aim_autoshoot
        || settings::aim_show_fov
        || settings::box_enabled
        || settings::skeleton_enabled
        || settings::health_enabled
        || settings::name_enabled
        || settings::headdot_enabled
        || settings::distance_enabled
        || settings::tool_enabled
        || settings::flags_team
        || settings::flags_state
        || settings::flags_health
        || settings::tracer_enabled
        || settings::oof_enabled
        || settings::walkspeed_enabled
        || settings::jumppower_enabled
        || settings::fov_enabled
        || settings::noclip_enabled
         || settings::freecam_enabled
         || settings::hipheight_enabled
        || settings::infjump_enabled
        || settings::hitsound_enabled
        || settings::time_enabled
        || settings::world_fog_enabled
        || settings::world_exposure_enabled;
}

static bool AnyGameFeatureActive()
{
    using namespace thenwefuckin;
    if (NeedsGameData())
        return true;
    return Menu::g_movement
            || Menu::g_explorerOpen
            || Menu::g_playerPreviewOpen;
}

namespace {
constexpr WORD C_WHITE  = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
constexpr WORD C_DIM    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
constexpr WORD C_GREEN  = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
constexpr WORD C_RED    = FOREGROUND_RED | FOREGROUND_INTENSITY;
constexpr WORD C_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
constexpr WORD C_CYAN   = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
constexpr const char* kIndent = "       ";

void badge(const char* label, WORD labelColor, const char* msg) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO old{};
    GetConsoleScreenBufferInfo(h, &old);
    std::cout << kIndent;
    SetConsoleTextAttribute(h, C_WHITE);
    std::cout << "[";
    SetConsoleTextAttribute(h, labelColor);
    std::cout << label;
    SetConsoleTextAttribute(h, C_WHITE);
    std::cout << "] ";
    SetConsoleTextAttribute(h, C_DIM);
    std::cout << msg << "\n";
    SetConsoleTextAttribute(h, old.wAttributes);
}

bool is_admin() {
    BOOL admin = FALSE;
    SID_IDENTIFIER_AUTHORITY nt = SECURITY_NT_AUTHORITY;
    PSID group = nullptr;
    if (AllocateAndInitializeSid(&nt, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0, &group)) {
        CheckTokenMembership(nullptr, group, &admin);
        FreeSid(group);
    }
    return admin != FALSE;
}

void relaunch_as_admin() {
    wchar_t exe[MAX_PATH]{};
    GetModuleFileNameW(nullptr, exe, MAX_PATH);
    SHELLEXECUTEINFOW sei{};
    sei.cbSize = sizeof(sei);
    sei.lpVerb = L"runas";
    sei.lpFile = exe;
    sei.nShow = SW_SHOWNORMAL;
    if (!ShellExecuteExW(&sei))
        badge("priv", C_RED, "elevation declined - run thenwefuckin.exe as administrator");
}

std::atomic<bool> g_overlayReady{false};
std::atomic<bool> g_firstFrame{false};

void on_terminate() {
    Logger::log("CRASH", "std::terminate (unhandled C++ exception?)");
    Logger::write_crash(nullptr, "terminate");
    MessageBoxA(nullptr, "thenwefuckin terminated unexpectedly.\nSee the .crash file on your Desktop.", "thenwefuckin crash", MB_ICONERROR);
    abort();
}
void __cdecl on_invalid_param(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t) {
    Logger::log("CRASH", "invalid CRT parameter");
    Logger::write_crash(nullptr, "invalid_parameter");

}
void __cdecl on_purecall() {
    Logger::log("CRASH", "pure virtual function call");
    Logger::write_crash(nullptr, "purecall");
    MessageBoxA(nullptr, "thenwefuckin crashed (purecall).\nSee the .crash file on your Desktop.", "thenwefuckin crash", MB_ICONERROR);
    _exit(3);
}
void on_sigabrt(int) {
    Logger::log("CRASH", "abort() called");
    Logger::write_crash(nullptr, "abort");
    _exit(3);
}

void stage_watcher(std::atomic<bool>& stop) {
    int shown = 0;
    while (!stop.load()) {
        if (shown < 1 && thenwefuckin::g_proc && thenwefuckin::g_proc->connected()) {
            shown = 1;
            char buf[192];
            snprintf(buf, sizeof(buf), "pid=%u base=0x%llX client=%s",
                (unsigned)thenwefuckin::g_proc->pid(),
                (unsigned long long)thenwefuckin::g_proc->base(),
                Offsets::ClientVersion.c_str());
            badge("attached", C_GREEN, buf);
            LOG("attach", buf);
        }
        if (shown < 2 && g_overlayReady.load()) {
            shown = 2;
            badge("overlay", C_GREEN, "DirectX ready");
            LOG("overlay", "DirectX ready");
        }
        if (shown < 3 && g_firstFrame.load()) {
            shown = 3;
            badge("ready", C_CYAN, "press INSERT for menu - have fun");
            LOG("boot", "ready");
            return;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
void target_watcher(std::atomic<bool>& stop) {
    while (!stop.load()) {
        for (int i = 0; i < 5 && !stop.load(); ++i)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (stop.load())
            return;
        if (thenwefuckin::g_proc && thenwefuckin::g_proc->connected() && !thenwefuckin::g_proc->alive()) {
            unsigned pid = (unsigned)thenwefuckin::g_proc->pid();
            thenwefuckin::g_proc->detach();
            char buf[160];
            snprintf(buf, sizeof(buf), "game closed (pid=%u) - handle parked, waiting for restart", pid);
            badge("left", C_YELLOW, buf);
            LOG("game", buf);
            Logger::note_session("no game (closed)");
        }
    }
}
}

int main()
{
    SetUnhandledExceptionFilter(CrashHandler);
    AddVectoredExceptionHandler(1, [](PEXCEPTION_POINTERS ep)->LONG {
        if (IsDebuggerPresent()) return EXCEPTION_CONTINUE_SEARCH;
        DWORD code = ep->ExceptionRecord->ExceptionCode;
        if (code == 0x406D1388 || code == 0x40010006 || code == 0x4001000A || code == 0xE06D7363 ||
            code == 0x80000003 || code == 0x80000004 ||
            (code >= 0x000006A4 && code <= 0x000007CF)) return EXCEPTION_CONTINUE_SEARCH;
        static long long lastMs=0; static int count=0;
        long long now = GetTickCount64();
        if (now - lastMs < 500) return EXCEPTION_CONTINUE_SEARCH;
        if (count++ > 20) return EXCEPTION_CONTINUE_SEARCH;
        lastMs = now;
        Logger::write_crash(ep, "VEH");
        return EXCEPTION_CONTINUE_SEARCH;
    });
    std::set_terminate(on_terminate);
    _set_invalid_parameter_handler(on_invalid_param);
    _set_purecall_handler(on_purecall);
    signal(SIGABRT, on_sigabrt);
    _set_abort_behavior(0, _WRITE_ABORT_MSG);
    Logger::quiet = true;
    Logger::init();

    thenwefuckin::syscalls::init();
    SetConsoleTitleA("thenwefuckin");

    std::cout << "\n";
    badge("thenwefuckin", C_CYAN, "external - INSERT to open menu");
    badge("discord", C_WHITE, "discord.gg/thenwefuckin");
    std::cout << "\n";

    HANDLE mutex = CreateMutexW(nullptr, FALSE, L"thenwefuckin-overlay-mutex");
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        badge("fail", C_RED, "thenwefuckin is already running");
        MessageBoxW(nullptr, L"thenwefuckin is already running.", L"thenwefuckin", MB_OK | MB_ICONINFORMATION);
        if (mutex) CloseHandle(mutex);
        return 0;
    }

    if (!is_admin()) {
        badge("priv", C_YELLOW, "administrator required - relaunching elevated...");
        relaunch_as_admin();
        if (mutex) CloseHandle(mutex);
        return 0;
    }
    badge("priv", C_GREEN, "running as administrator");
    badge("attaching", C_GREEN, "waiting for RobloxPlayerBeta.exe...");
    LOG("boot", "session start");

    std::atomic<bool> stopWatcher{false};
    std::thread watcher(stage_watcher, std::ref(stopWatcher));
    std::atomic<bool> stopTargetWatch{false};
    std::thread targetWatch(target_watcher, std::ref(stopTargetWatch));

    OverlayConfig cfg;
    cfg.windowTitle = L" ";
    cfg.targetWindow = L"";

    Overlay overlay(cfg);
    if (!overlay.Initialize())
    {
        badge("fail", C_RED, "failed to initialize overlay - see thenwefuckin_log.txt");
        LOG("overlay", "Initialize failed");
        MessageBoxW(nullptr, L"Failed to initialize overlay", L"Error", MB_OK);
        stopWatcher.store(true);
        if (watcher.joinable()) watcher.join();
        stopTargetWatch.store(true);
        if (targetWatch.joinable()) targetWatch.join();
        if (mutex) CloseHandle(mutex);
        return 1;
    }
    g_overlayReady.store(true);

    overlay.SetRenderCallback([](ImDrawList* dl, int width, int height, float fps, bool menuOpen) {
        (void)menuOpen;
        g_firstFrame.store(true);

        static double lastAttachTry = -10.0;
        static double lastRefresh = -10.0;
        static double lastPfCache = -10.0;
        double now = ImGui::GetTime();

        bool needGame = NeedsGameData();
        bool overlayActive = needGame || Menu::g_movement || Menu::g_explorerOpen || Menu::g_playerPreviewOpen;

        if ((!thenwefuckin::g_proc || !thenwefuckin::g_proc->connected()))
        {
            if (now - lastAttachTry > 2.0)
            {
                lastAttachTry = now;
                thenwefuckin::g_proc->attach("RobloxPlayerBeta.exe");
            }
        }
        else if (needGame)
        {

            if (now - lastRefresh >= 0.008)
            {
                lastRefresh = now;

                thenwefuckin::g_ctx.refresh();

                thenwefuckin::math::vec3 lv = thenwefuckin::g_ctx.local_velocity;
                bool ok = thenwefuckin::g_ctx.ready && thenwefuckin::g_ctx.local_root
                          && std::isfinite(lv.x) && std::isfinite(lv.y) && std::isfinite(lv.z);
                g_localSpeed = ok ? sqrtf(lv.x * lv.x + lv.z * lv.z) : -1.0f;
            }
        }
        else
        {
            g_localSpeed = -1.0f;
        }

        if (thenwefuckin::g_proc && thenwefuckin::g_proc->connected() && now - lastPfCache >= 0.016)
        {
            lastPfCache = now;
            PfCache::update();
        }

        {
            using namespace thenwefuckin;
            static double lastSessionCheck = -10.0;
            static uint64_t s_place = 0;
            static uint64_t s_dm = 0;
            static int s_zeroCount = 0;
            if (now - lastSessionCheck >= 0.5)
            {
                lastSessionCheck = now;
                bool conn = g_proc && g_proc->connected();
                uint64_t dmAddr = 0;
                uint64_t place = 0;
                if (conn)
                {
                    dmAddr = g_ctx.datamodel.addr;
                    if (!dmAddr)
                    {
                        uint64_t fake = g_proc->read<uint64_t>(g_proc->base() + Offsets::FakeDataModel::Pointer);
                        if (fake) dmAddr = g_proc->read<uintptr_t>(fake + Offsets::FakeDataModel::RealDataModel);
                    }
                    if (dmAddr) place = g_proc->read<uint64_t>(dmAddr + Offsets::DataModel::PlaceId);
                }
                if (!conn)
                {
                    if (s_place != 0)
                    {
                        settings::push_state();
                        settings::disable_all();
                        badge("left", C_YELLOW, "disconnected - all features disabled");
                        LOG("game", "disconnected - all features disabled");
                        Logger::note_session("disconnected");
                    }
                    s_place = 0; s_dm = 0; s_zeroCount = 0;
                }
                else if (place != 0 && place != s_place)
                {
                    if (s_place != 0)
                    {
                        settings::push_state();
                        settings::disable_all();
                        char lb[96];
                        snprintf(lb, sizeof(lb), "left %llu - all features disabled", (unsigned long long)s_place);
                        badge("left", C_YELLOW, lb);
                        LOG("game", lb);
                    }
                    s_place = place; s_dm = dmAddr; s_zeroCount = 0;
                    char jb[96];
                    snprintf(jb, sizeof(jb), "joined place id %llu", (unsigned long long)place);
                    badge("game", C_GREEN, jb);
                    LOG("game", jb);
                    Logger::note_session(jb);
                    thenwefuckin::visual::on_game_joined();
                    if (settings::restore_state())
                    {
                        badge("game", C_CYAN, "features restored");
                        LOG("game", "features restored");
                    }
                }
                else if (place != 0 && dmAddr != 0 && dmAddr != s_dm)
                {

                    s_dm = dmAddr; s_zeroCount = 0;
                    thenwefuckin::visual::on_game_joined();
                    char jb[128];
                    snprintf(jb, sizeof(jb), "rejoined place id %llu (new server)", (unsigned long long)place);
                    badge("game", C_YELLOW, jb);
                    LOG("game", jb);
                    Logger::note_session(jb);
                }
                else if (place == 0 && s_place != 0)
                {
                    if (++s_zeroCount >= 2)
                    {
                        settings::push_state();
                        settings::disable_all();
                        char lb[96];
                        snprintf(lb, sizeof(lb), "left %llu - all features disabled", (unsigned long long)s_place);
                        badge("left", C_YELLOW, lb);
                        LOG("game", lb);
                        Logger::note_session("left game");
                        s_place = 0; s_dm = 0; s_zeroCount = 0;
                    }
                }
                else s_zeroCount = 0;
            }
        }

        bool anythingToDraw = g_menuOpen || Menu::g_watermark || Menu::g_keybinds
                              || Menu::g_movement || Menu::g_internalDebug || overlayActive;
        Overlay::SetRenderEnabled(anythingToDraw);

        float frameCap = 0.0f;
        if (g_menuOpen)
        {
            frameCap = 1.0f / 120.0f;
        }
        Overlay::SetFrameInterval(frameCap);

        static double lastDebugBuild = -10.0;
        if (Menu::g_internalDebug && now - lastDebugBuild >= 1.0)
        {
            lastDebugBuild = now;
            PrintDebugLines(fps);
        }

        Logger::quiet = true;

        Menu::RenderWatermark(dl, width, fps);
        Menu::RenderKeybinds(dl, width, height);
        Menu::RenderMovement(dl, width, height);
        Menu::RenderInternalDebug(dl, width, height, fps);
        Menu::RenderNavBar(dl, width, height);
        Menu::Render();
        Menu::RenderSettingsPanel();
        Menu::RenderThemePanel();
        Menu::RenderExplorerPanel();
        Menu::RenderPlayerPreviewPanel();

        if (needGame)
        {
            thenwefuckin::aim::run(width, height);
            thenwefuckin::visual::render(dl, width, height);
        }

        thenwefuckin::misc::run();
    });

    overlay.SetVSync(g_vsync);
    overlay.SetStreamProof(g_streamProof);
    Overlay::SetMenuOpen(true);

    std::atomic<bool> stopFreecam{false};
    std::thread freecamThread(thenwefuckin::misc::freecam::thread_main, std::ref(stopFreecam));

    overlay.Run();
    stopFreecam.store(true, std::memory_order_relaxed);
    if (freecamThread.joinable()) freecamThread.join();
    thenwefuckin::aim::viewport::shutdown();
    thenwefuckin::aim::raycast::shutdown();
    thenwefuckin::aim::wraith::shutdown();
    stopWatcher.store(true);
    if (watcher.joinable()) watcher.join();
    stopTargetWatch.store(true);
    if (targetWatch.joinable()) targetWatch.join();
    badge("done", C_GREEN, "session ended cleanly");
    LOG("boot", "session end");
    if (mutex) CloseHandle(mutex);
    return 0;
}
