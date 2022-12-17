cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SCRIPT_SOURCES
        scripts/PlayerMovementScript.cpp
        scripts/ProjectilePoolScript.cpp
        scripts/ProjectileScript.cpp
        scripts/SaveStateScript.cpp
        scripts/SaveGameTestScripts/SaveGameTestScript.cpp
        scripts/SaveGameTestScripts/ShotCounterScript.cpp
        scripts/PlayerShootScript.cpp
        scripts/PlayerCollisionScript.cpp
        scripts/GameManagerScript.cpp
        scripts/EnemyMovementScript.cpp
        scripts/EnemyCollisionScript.cpp
        scripts/MenuScripts/StartGameButtonScript.cpp
        scripts/MenuScripts/SelectLevelButtonScript.cpp
        scripts/MenuScripts/BackButtonScript.cpp
        scripts/MenuScripts/SettingsButtonScript.cpp
        scripts/MenuScripts/MasterVolumeButtonScript.cpp
        scripts/MenuScripts/SoundEffectVolumeButtonScript.cpp
        scripts/MenuScripts/FullScreenButtonScript.cpp
        scripts/MenuScripts/ExitButtonScript.cpp
        scripts/MenuScripts/TextUpdateScript.cpp
        scripts/MenuScripts/MusicVolumeButtonScript.cpp
        scripts/MenuScripts/KeyConfigButtonScript.cpp
        scripts/GameManagerScript.cpp
        scripts/HUDScript.cpp)

set(GAMEOBJECTS_SOURCES
        gameobjects/PlayerObject.cpp     
        gameobjects/Wall.cpp
        gameobjects/Projectile.cpp
        gameobjects/ProjectilePoolObject.cpp
        gameobjects/TestBlock.cpp
        gameobjects/GameManager.cpp
        gameobjects/HUD.cpp
        gameobjects/EnemyObject.cpp)

set(SCENE_SOURCES
        scenes/PlayerTestScene.cpp
        scenes/SaveGameTestScene.cpp
        scenes/MainMenuScene.cpp
        scenes/SelectLevelScene.cpp
        scenes/SettingsScene.cpp)

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
