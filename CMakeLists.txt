cmake_minimum_required(VERSION 3.23)
project(GolfEngine)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Package paths
if(WIN32)
    #Windows specific packages
    set(SDL2_DIR libs/sdl2/cmake)
    set(SDL2_MIXER_DIR libs/sdl2_mixer/cmake)
    set(SDL2_IMAGE_DIR libs/sdl2_image/cmake)
    set(SDL2_TTF_DIR libs/sdl2_ttf/cmake)
endif()
set(IMGUI_DIR libs/imgui/cmake)
set(PUGIXML_DIR libs/pugixml/cmake)

# Packages
find_package(SDL2 REQUIRED)
find_package(IMGUI REQUIRED)
find_package(PUGIXML)
find_package(SDL2_MIXER REQUIRED) #Include dirs is included on target_link_libraries call
find_package(SDL2_IMAGE REQUIRED) #Include dirs is included on target_link_libraries call
find_package(SDL2_TTF REQUIRED) #Include dirs is included on target_link_libraries call
add_subdirectory(libs/box2d-2.4.1) #Include dirs is included on target_link_libraries call

# Includes
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${IMGUI_INCLUDE_DIRS})
include_directories(${PUGIXML_INCLUDE_DIRS})

#Source Files
set(INPUT_SOURCES
        src/Input/ActionMap.cpp)

set(SERVICES_SOURCES
        src/Services/Box2DPhysicsService.cpp
        src/Services/SDLAudioService.cpp
        src/Services/SDLRenderService.cpp
        src/Services/SDLInputService.cpp
        src/Services/Singletons/PhysicsSingleton.cpp
        src/Services/Singletons/AudioSingleton.cpp
        src/Services/Singletons/RenderSingleton.cpp
        src/Services/Singletons/InputSingleton.cpp
        src/Services/Render/Texture.cpp
        src/Services/PugiXMLTileMapParserService.cpp
        src/Services/Singletons/TileMapParserSingleton.cpp)

set(SCENE_SOURCES
        src/Scene/Scene.cpp
        src/Scene/GameObjects/GameObject.cpp
        src/Scene/Components/AudioSource.cpp
        src/Scene/Components/Animator.cpp
        src/Scene/Components/ParticleSystem.cpp
        src/Scene/Components/Pathfinding.cpp
        src/Scene/RenderShape/LineRenderShape.cpp
        src/Scene/RenderShape/RectRenderShape.cpp
        src/Scene/RenderShape/CircleRenderShape.cpp
        src/Scene/RenderShape/SpriteRenderShape.cpp
        src/Scene/RenderShape/ButtonRenderShape.cpp
        src/Scene/RenderShape/ParticleSystemRenderShape.cpp
        src/Scene/RenderShape/TextRenderShape.cpp
        src/Scene/GameObjects/UIObject/Button.cpp
        src/Scene/GameObjects/UIObject/Text.cpp
        src/Scene/Components/RigidBody.cpp
        src/Scene/Components/BoxCollider.cpp
        src/Scene/Components/CircleCollider.cpp
        src/Scene/Components/SpriteComponent.cpp
        src/Scene/Components/TiledComponent.cpp
        src/Scene/RenderShape/TileMapRenderShape.cpp)

set(CORE_SOURCES
        src/Core/GameLoop.cpp
        src/Core/SceneManager.cpp
        src/Core/ProjectSettings.cpp
        src/Core/Time.cpp
        src/Scene/RenderShape/TextRenderShape.cpp)

# Main Project
add_library(${PROJECT_NAME}
        ${SCENE_SOURCES}
        ${SERVICES_SOURCES}
        ${INPUT_SOURCES}
        ${CORE_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ./src)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_mixer::SDL2_mixer)
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} SDL2_ttf::SDL2_ttf)
target_link_libraries(${PROJECT_NAME} box2d)
target_link_libraries(${PROJECT_NAME} PUGIXML)

# Sub Projects
add_subdirectory(tests)

add_subdirectory(validation/US09_Animations)
add_subdirectory(validation/US03_InputService)
add_subdirectory(validation/US12_AudioService)
add_subdirectory(validation/US00_Rendering)
add_subdirectory(validation/US04_RenderFPS)
add_subdirectory(validation/US08_RenderUIObject)
add_subdirectory(validation/US14_PhysicsService)
add_subdirectory(validation/US00_AllServices)
add_subdirectory(validation/US00_TileMap)
