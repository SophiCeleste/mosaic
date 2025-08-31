# Mosaic

Mosaic is a personal project to design and implement a lightweight 2D game engine in C++ from the ground up.  
It provides core systems for rendering, input, scripting, and tile-based maps with pixel-art graphics.  
The goal is to create a flexible foundation that can support JRPG, dungeon crawler, tactics, or hybrid mechanics in the future.

---

## Features (Current & Planned)

- **Core engine loop**
  - Fixed-timestep update with interpolation  
  - Deterministic simulation independent of render framerate  

- **Rendering**
  - SDL2 window + renderer abstraction  
  - Pixel-art friendly scaling  
  - Placeholder rectangle sprite (to be replaced with texture batching)  

- **Input**
  - Unified keyboard input → semantic actions (up, down, confirm, cancel)  
  - Edge detection for button presses  

- **Scripting**
  - Embedded Lua 5.4 (LuaJIT optional)  
  - Configurable parameters (e.g. player speed) exposed to Lua  
  - Future: game logic and encounter tables in Lua  

- **Tile-based world**
  - Planned: Tiled (TMX/JSON) map loader  
  - Planned: camera system + visible tile culling  
  - Planned: collision from tile layers  

- **Game state**
  - Planned: simple ECS for entities (player, NPCs, interactables)  
  - Planned: state machines for overworld, menus, and battles  

---

## Build Instructions (Windows, MSVC + vcpkg)

### Prerequisites
- [Visual Studio 2022](https://visualstudio.microsoft.com/) with Desktop C++ workload  
- [CMake ≥ 3.20](https://cmake.org/)  
- [vcpkg](https://github.com/microsoft/vcpkg) for dependencies  

### Setup
```powershell
git clone https://github.com/SophiCeleste/mosaic
cd mosaic

# install dependencies
$env:USERPROFILE\vcpkg\vcpkg.exe install sdl2:x64-windows lua:x64-windows

# configure + build
cmake -S . -B build `
  -G "Visual Studio 17 2022" -A x64 `
  -DCMAKE_TOOLCHAIN_FILE=$env:USERPROFILE\vcpkg\scripts\buildsystems\vcpkg.cmake `
  -DVCPKG_TARGET_TRIPLET=x64-windows `
  -DCMAKE_BUILD_TYPE=RelWithDebInfo

cmake --build build --config RelWithDebInfo
```

---

## Run
```powershell
.\build\RelWithDebInfo\mosaic.exe
```

---

## Repository Structure

```text
assets/            # Scripts and future art/maps
  scripts/
    init.lua       # Example Lua config

src/               # Engine source
  Engine.*         # Main engine loop
  Renderer.*       # SDL2 renderer wrapper
  Input.*          # Input state abstraction
  Time.*           # Fixed-timestep accumulator
  ScriptSystem.*   # Lua integration
  main.cpp         # Entry point
```

---

## License

This project is source-available for reference only.
All rights are reserved by the author.
The code may not be copied, modified, or redistributed without permission.
See [LICENSE.txt](LICENSE.txt) for full terms.

---

## Author

Developed by Sophia Celeste
