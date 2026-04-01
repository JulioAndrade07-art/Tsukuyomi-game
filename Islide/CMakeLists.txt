cmake_minimum_required(VERSION 3.10)
project(Runner2DGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the SFML_DIR so CMake can find SFMLConfig.cmake
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-3.0.2/lib/cmake/SFML")

# Find SFML components
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

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

# Link SFML
target_link_libraries(Runner2DGame PRIVATE SFML::Graphics SFML::Window SFML::System)
