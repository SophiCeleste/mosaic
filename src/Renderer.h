#pragma once
#include <SDL.h>
#include <cstdint>

/** 
 * @brief Renderer wraps SDL_Window and SDL_Renderer.
 *
 * Abstract behind a small interface to enable swapping to a different backend later.
 */
class Renderer {
public:
    /// Create window and rendere; returns false on failure.
    bool init(const char* title, int w, int h);
    /// Begin a new frame with a solid clear color.
    void beginFrame(uint8_t r, uint8_t g, uint8_t b);
    /// Draw a test rectangle; stand-in for sprite batching initially.
    void drawRect(int x, int y, int w, int h);
    /// Present the back buffer
    void endFrame();
    /// Destroy resources.
    void shutdown();

    SDL_Window* window() const { return window_; }
    SDL_Renderer* sdl() const { return renderer_; }

private:
    SDL_Window* window_ { nullptr };
    SDL_Renderer* renderer_ { nullptr };
};
