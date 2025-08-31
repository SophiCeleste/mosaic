#include "Engine.h"
#include "Input.h"
#include <SDL.h>
#include <cstdio>

bool Engine::init(const char* title, int w, int h) {
    if (!renderer_.init(title, w, h)) return false;
    if (!scripts_.init()) return false;

    // Load boot script; ignore failure for now but log it
    if (!scripts_.runFile("assets/scripts/init.lua")) {
        std::fprintf(stderr, "Failed to load init.lua; using defaults\n");
    }
    // Query scripted parameter
    playerSpeed_ = scripts_.queryPlayerSpeed(playerSpeed_);

    running_ = true;
    return true;
}

void Engine::pollInput(InputState& io) {
    // Save previous for edge detection
    //io.prev = io;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) io.quit = true;

        if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            bool down = (e.type == SDL_KEYDOWN);
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE: io.cancel = down; break;
                case SDLK_RETURN: io.confirm = down; break;
                case SDLK_UP:     io.up = down; break;
                case SDLK_DOWN:   io.down = down; break;
                case SDLK_LEFT:   io.left = down; break;
                case SDLK_RIGHT:  io.right = down; break;
                default: break;
            }
        }
    }
}

void Engine::update(const TimeStep& step, const InputState& io) {
    // Movement in simulation space; one pixel per unit, scaled by dt
    const double dist = playerSpeed_ * step.seconds;

    if (io.up)    playerY_ -= dist;
    if (io.down)  playerY_ += dist;
    if (io.left)  playerX_ -= dist;
    if (io.right) playerX_ += dist;

    // Quit on ESC rising edge
    if (pressed(io.cancel, prevIo_.cancel)) {
        running_ = false;
    }
}

void Engine::render(double /*alpha*/) {
    renderer_.beginFrame(25, 25, 35);
    // Draw the "player" as a 16x16 white square
    renderer_.drawRect(static_cast<int>(playerX_), static_cast<int>(playerY_), 16, 16);
    renderer_.endFrame();
}

void Engine::run() {
    const TimeStep step { 1.0 / 60.0};

    InputState io {};
    Uint64 freq = SDL_GetPerformanceFrequency();
    Uint64 last = SDL_GetPerformanceCounter();

    while (running_) {
        // time
        Uint64 now = SDL_GetPerformanceCounter();
        double dt = static_cast<double>(now - last) / static_cast<double>(freq);
        last = now;

        // input: first copy current to prev, then poll into current
        prevIo_ = io;
        pollInput(io);

        int steps = clock_.accumulate(dt, step);

        // Avoid runaway if window loses focus for a while; max steps = 8
        if (steps > 8) steps = 8;

        for (int i = 0; i < steps; ++i) {
            update(step, io);
        }

        render(clock_.alpha(step));

        if (io.quit) running_ = false;
    }
}

void Engine::shutdown() {
    scripts_.shutdown();
    renderer_.shutdown();
}









