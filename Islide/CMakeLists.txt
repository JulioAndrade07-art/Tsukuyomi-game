cmake_minimum_required(VERSION 3.10)
project(Runner2DGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Directories
include_directories(.)

# Source files
set(SOURCES
    main.cpp
    engine/Game.cpp
    player/Player.cpp
    player/PlayerState.cpp
    systems/InputHandler.cpp
    systems/ProgressionSystem.cpp
    enemies/EnemyFactory.cpp
    ui/HUD.cpp
    biomes/BiomeContext.cpp
)

# Executable
add_executable(Runner2DGame ${SOURCES})
