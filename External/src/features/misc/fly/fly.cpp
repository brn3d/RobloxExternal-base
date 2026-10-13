#include "fly.h"
#include "../../../utility/cache/cache.h"
#include "../../../utility/global/globals.h"
#include "../../../menu/overlay/settings.h"
#include "../../../menu/core/gui/menu.h"
#include <Windows.h>
#include <algorithm>
#include <chrono>
namespace thenwefuckin::misc::fly
{
    namespace
    {
        bool s_wasEnabled = false;
        std::chrono::steady_clock::time_point s_lastTick{};
        uintptr_t s_lastRootPrim = 0;
        uintptr_t s_anchoredPrim = 0;
        bool s_savedAnchored = false;

        void set_collide(const node& character, bool collide)
        {
            if (!character)
                return;
            for (auto& part : character.children())
            {
                uintptr_t prim = part.primitive();
                if (!prim)
                    continue;
                uint8_t flags = g_proc->read<uint8_t>(prim + Offsets::Primitive::PrimitiveFlags);
                bool has = (flags & Offsets::PrimitiveFlags::CanCollide) != 0;
                if (has == collide)
                    continue;
                uint8_t next = collide
                    ? static_cast<uint8_t>(flags | Offsets::PrimitiveFlags::CanCollide)
                    : static_cast<uint8_t>(flags & ~Offsets::PrimitiveFlags::CanCollide);
                g_proc->write<uint8_t>(prim + Offsets::Primitive::PrimitiveFlags, next);
            }
        }

        bool roblox_foreground()
        {
            if (!g_proc || !g_proc->connected())
                return false;
            HWND fg = GetForegroundWindow();
            if (!fg)
                return false;
            DWORD pid = 0;
            GetWindowThreadProcessId(fg, &pid);
            return pid != 0 && pid == g_proc->pid();
        }

        void stop_motion(uintptr_t prim)
        {
            if (!prim)
                return;
            math::vec3 zero{};
            g_proc->write<math::vec3>(prim + Offsets::Primitive::AssemblyLinearVelocity, zero);
            g_proc->write<math::vec3>(prim + Offsets::Primitive::AssemblyAngularVelocity, zero);
        }

        void set_anchored(uintptr_t prim, bool anchored)
        {
            if (!prim || !g_proc || !g_proc->connected())
                return;
            uint8_t flags = g_proc->read<uint8_t>(prim + Offsets::Primitive::PrimitiveFlags);
            bool has = (flags & Offsets::PrimitiveFlags::Anchored) != 0;
            if (has == anchored)
                return;
            uint8_t next = anchored
                ? static_cast<uint8_t>(flags | Offsets::PrimitiveFlags::Anchored)
                : static_cast<uint8_t>(flags & ~Offsets::PrimitiveFlags::Anchored);
            g_proc->write<uint8_t>(prim + Offsets::Primitive::PrimitiveFlags, next);
        }

        bool is_anchored(uintptr_t prim)
        {
            if (!prim || !g_proc || !g_proc->connected())
                return false;
            uint8_t flags = g_proc->read<uint8_t>(prim + Offsets::Primitive::PrimitiveFlags);
            return (flags & Offsets::PrimitiveFlags::Anchored) != 0;
        }
    }

    void run()
    {
        bool active = settings::fly_enabled;
        if (active && settings::fly_key != 0)
        {
            active = Menu::IsMenuKeyActive("##fly_key", settings::fly_key, settings::fly_key_mode);
        }
        if (!active && !s_wasEnabled)
            return;
        if (!g_proc || !g_proc->connected())
        {
            s_wasEnabled = false;
            s_anchoredPrim = 0;
            s_lastRootPrim = 0;
            return;
        }
        if (!active)
        {

            node character = g_ctx.get_character(g_ctx.local_player);
            if (character)
                set_collide(character, true);
            node root = g_ctx.local_root;
            uintptr_t unanchorPrim = root ? root.primitive() : 0;
            if (s_anchoredPrim && unanchorPrim && unanchorPrim == s_anchoredPrim)
                set_anchored(unanchorPrim, s_savedAnchored);
            s_anchoredPrim = 0;
            if (root)
                stop_motion(root.primitive());
            s_wasEnabled = false;
            return;
        }
        if (!g_ctx.ready || !g_ctx.local_root || !g_ctx.camera)
            return;

        node humanoid = g_ctx.local_humanoid;
        if (humanoid)
        {
            float hp = g_proc->read<float>(humanoid.addr + Offsets::Humanoid::Health);
            if (hp <= 0.0f)
                return;

            uintptr_t seat = g_proc->read<uintptr_t>(humanoid.addr + Offsets::Humanoid::SeatPart);
            if (seat != 0)
                return;
        }

        auto now = std::chrono::steady_clock::now();
        float dt = 0.016f;
        if (s_wasEnabled)
        {
            dt = std::chrono::duration<float>(now - s_lastTick).count();
            if (dt > 0.05f) dt = 0.05f;
            if (dt <= 0.0f) dt = 0.000001f;
        }
        s_lastTick = now;

        node root = g_ctx.local_root;
        uintptr_t prim = root.primitive();
        if (!prim)
            return;

        if (prim != s_lastRootPrim)
        {
            s_lastRootPrim = prim;
            s_anchoredPrim = 0;
        }

        node character = g_ctx.get_character(g_ctx.local_player);
        if (character)
            set_collide(character, false);

        math::frame cf = g_proc->read<math::frame>(g_ctx.camera.addr + Offsets::Camera::Rotation);
        math::vec3 forward{ -cf.rot[2], -cf.rot[5], -cf.rot[8] };
        math::vec3 right{ cf.rot[0], cf.rot[3], cf.rot[6] };
        if (forward.length() < 0.000001f || right.length() < 0.000001f)
            return;
        forward = forward.normalized();
        right = right.normalized();
        const math::vec3 worldUp{ 0.0f, 1.0f, 0.0f };

        float fwdIn = 0.0f, sideIn = 0.0f, upIn = 0.0f;
        if (!g_menuOpen && roblox_foreground())
        {
            if (GetAsyncKeyState('W') & 0x8000) fwdIn += 1.0f;
            if (GetAsyncKeyState('S') & 0x8000) fwdIn -= 1.0f;
            if (GetAsyncKeyState('D') & 0x8000) sideIn += 1.0f;
            if (GetAsyncKeyState('A') & 0x8000) sideIn -= 1.0f;
            if (GetAsyncKeyState(VK_SPACE) & 0x8000) upIn += 1.0f;
            if (GetAsyncKeyState('E') & 0x8000) upIn += 1.0f;
            if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) || (GetAsyncKeyState(VK_RCONTROL) & 0x8000)) upIn -= 1.0f;
            if (GetAsyncKeyState('C') & 0x8000) upIn -= 1.0f;
            if (GetAsyncKeyState('Q') & 0x8000) upIn -= 1.0f;
        }

        const float speed = std::clamp(settings::fly_speed, 5.0f, 500.0f);
        math::vec3 curPos = g_proc->read<math::vec3>(prim + Offsets::Primitive::Position);

        math::vec3 move = forward * fwdIn + right * sideIn + worldUp * upIn;
        if (move.length() > 0.000001f)
        {

            if (s_anchoredPrim == prim)
            {
                set_anchored(prim, s_savedAnchored);
                s_anchoredPrim = 0;
            }
            move = move.normalized();
            math::vec3 newPos = curPos + move * (speed * dt);
            g_proc->write<math::vec3>(prim + Offsets::Primitive::Position, newPos);
            math::vec3 vel = move * speed;
            g_proc->write<math::vec3>(prim + Offsets::Primitive::AssemblyLinearVelocity, vel);
            g_proc->write<math::vec3>(prim + Offsets::Primitive::AssemblyAngularVelocity, math::vec3{});
        }
        else
        {

            if (s_anchoredPrim != prim)
            {
                s_savedAnchored = is_anchored(prim);
                s_anchoredPrim = prim;
            }
            set_anchored(prim, true);
        }
        s_wasEnabled = true;
    }
}
