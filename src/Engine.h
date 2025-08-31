#pragma once

struct TimeStep;
struct InputState;

#include "Renderer.h"
#include "Input.h"
#include "Time.h"
#include "ScriptSystem.h"

/** @brief Engine wires together platform, script, update, and render passes.
 *
 * Start small: one moving rectangle as the "player."
 */
class Engine {
public:
    bool init(const char* title, int w, int h);
    void run();
    void shutdown();

private:
    void pollInput(InputState& io);
    void update(const TimeStep& step, const InputState& io);
    void render(double alpha);

private:
    Renderer renderer_;
    ScriptSystem scripts_;
    FrameClock clock_;

    // Demo state: player position in simulation space
    double playerX_ { 50.0 };
    double playerY_ { 50.0 };
    double playerSpeed_ { 100.0 };  // pixels per second, overwritten by Lua
    bool running_ { false };
    InputState prevIo_ {};
};
