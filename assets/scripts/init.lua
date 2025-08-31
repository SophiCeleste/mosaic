-- init.lua: called once at boot by C++
Game = {
    player_speed = 120.0, -- pixels per second
}

-- Example of a scripted rule readable from C++
function Get_player_speed()
    return Game.player_speed
end
