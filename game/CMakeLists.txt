cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SCRIPT_SOURCES scripts/PlayerMovementScript.cpp scripts/ProjectilePoolScript.cpp scripts/ProjectileScript.cpp
        scripts/SaveStateScript.cpp scripts/SaveStateScript.h scripts/StartGameButtonScript.cpp
        scripts/SelectLevelButtonScript.cpp scripts/BackButtonScript.cpp scripts/SettingsButtonScript.cpp
        scripts/MasterVolumeButtonScript.cpp scripts/SoundEffectVolumeButtonScript.cpp scripts/FullScreenButtonScript.cpp
        scripts/ExitButtonScript.cpp scripts/VolumeTextUpdateScript.cpp scripts/MusicVolumeButtonScript.cpp
        scripts/KeyConfigButtonScript.cpp)
set(GAMEOBJECTS_SOURCES
        gameobjects/PlayerObject.cpp
        gameobjects/Wall.cpp gameobjects/Projectile.cpp gameobjects/Projectile.h gameobjects/ProjectilePoolObject.cpp gameobjects/ProjectilePoolObject.h gameobjects/TestBlock.cpp gameobjects/TestBlock.h)
set(SCENE_SOURCES scenes/PlayerTestScene.cpp scenes/MainMenuScene.cpp scenes/SelectLevelScene.cpp scenes/SettingsScene.cpp scenes/KeyConfigScene.cpp)

# Resource files
add_custom_target(Game_Resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)

# Main Project
add_executable(Game
        ${SCRIPT_SOURCES}
        ${GAMEOBJECTS_SOURCES}
        ${SCENE_SOURCES}
        main.cpp)
target_link_libraries(Game GolfEngine)
add_dependencies(Game Game_Resources)
