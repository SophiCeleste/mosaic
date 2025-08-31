#pragma once

/** 
 * @brief Simple input snapshot; engine keeps a separate "previous" copy.
 */
struct InputState {
    bool up {false}, down {false}, left {false}, right {false};
    bool confirm {false}, cancel {false};
    bool quit {false};
};

/**
 * @brief Rising-edge helper for booleans.
 */
inline bool pressed(bool now, bool was) { return now && !was; }
