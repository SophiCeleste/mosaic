#include "ScriptSystem.h"
#include <cstdio>

bool ScriptSystem::init() {
    L_ = luaL_newstate();
    if (!L_) return false;
    luaL_openlibs(L_);
    return true;
}

bool ScriptSystem::runFile(const std::string& path) {
    // luaL_dofile = load + pcall; returns nonzero on error
    if (luaL_dofile(L_, path.c_str()) != LUA_OK) {
        const char* msg = lua_tostring(L_, -1);
        std::fprintf(stderr, "Lua error: %s\n", msg ? msg : "(unknown)");
        lua_pop(L_, 1); // pop error message
        return false;
    }
    return true;
}

double ScriptSystem::queryPlayerSpeed(double defaultSpeed) const {
    if (!L_) return defaultSpeed;
    lua_getglobal(L_, "Get_player_speed");  // push function
    if (!lua_isfunction(L_, -1)) {
        lua_pop(L_, 1);
        return defaultSpeed;
    }
    if (lua_pcall(L_, 0, 1, 0) != LUA_OK) {
        const char* msg = lua_tostring(L_, -1);
        std::fprintf(stderr, "Lua error in Get_player_speed: %s\n", msg ? msg : "(unknown)");
        lua_pop(L_, 1);
        return defaultSpeed;
    }
    double speed = defaultSpeed;
    if (lua_isnumber(L_, -1)) {
        speed = lua_tonumber(L_, -1);
    }
    lua_pop(L_, 1);  // pop return value
    return speed;
}

void ScriptSystem::shutdown() {
    if (L_) { lua_close(L_); L_ = nullptr; }
}
