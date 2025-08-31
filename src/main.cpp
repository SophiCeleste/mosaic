#include "Engine.h"
#include <cstdio>

/**
 * @brief Entry point. Creates the engine, runs the main loop, and shuts down cleanly.
 */
int main(int argc, char** argv) {
    (void)argc; (void)argv;

    Engine engine;
    if (!engine.init("Mosaic", 800, 600)) {
        std::fprintf(stderr, "Engine init failed\n");
        return 1;
    }
    engine.run();
    engine.shutdown();
    return 0;
}
