#pragma once
#include <cstdint>
namespace thenwefuckin::misc::spectate
{
    // Follows the target with the game camera (CameraSubject = target humanoid).
    // Tick is driven from misc::run() every frame.
    void toggle(uintptr_t playerAddr);
    void stop();
    bool active();
    bool is_spectating(uintptr_t playerAddr);
    uintptr_t target();
    // Moves the local character next to the target. Returns false on failure.
    bool teleport_to(uintptr_t playerAddr);
    void run();
}
