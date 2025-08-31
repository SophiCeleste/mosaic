#pragma once
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <string>

/** 
 * @brief ScriptSystem owns a Lua state and provides utility calls.
 *
 * Keep the C API wrapper tiny; add binding helpers later if needed.
 */
class ScriptSystem {
public:
    /// Create a fresh Lua state and open standard libraries.
    bool init();
    /// Load and execute a Lua file; returns false if any error occurs.
    bool runFile(const std::string& path);
    /// Call Lua function `Get_player_speed()`; return defaultSpeed on failure.
    double queryPlayerSpeed(double defaultSpeed) const;
    /// Destroy the Lua state.
    void shutdown();

    lua_State* L() const { return L_; }

private:
    lua_State* L_ { nullptr };
};
