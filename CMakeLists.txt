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
endif()
set(IMGUI_DIR libs/imgui/cmake)

# Packages
find_package(SDL2 REQUIRED)
find_package(IMGUI REQUIRED)
find_package(SDL2_MIXER REQUIRED) #Include dirs is included on target_link_libraries call
find_package(SDL2_IMAGE REQUIRED) #Include dirs is included on target_link_libraries call

# Includes
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${IMGUI_INCLUDE_DIRS})

#Source Files
set(INPUT_SOURCES
        src/Input/ActionMap.cpp)

set(SERVICES_SOURCES
        src/Services/Box2DPhysicsService.cpp
        src/Services/SDLAudioService.cpp
        src/Services/SDLRenderService.cpp
        src/Services/SDLInputService.cpp
        src/Services/Singletons/RenderSingleton.cpp
        src/Services/Render/Texture.cpp)
set(SCENE_SOURCES
        src/Scene/Scene.cpp
        src/Scene/GameObjects/GameObject.cpp
        src/Scene/Components/AudioSource.cpp
        src/Scene/Components/Component.cpp
        src/Scene/Components/BehaviourScript.cpp
        src/Scene/Components/Drawable.cpp
        src/Scene/Components/Animator.cpp
        src/Scene/Components/ParticleSystem.cpp
        src/Scene/Components/Pathfinding.cpp
        src/Scene/RenderShape/LineRenderShape.cpp
        src/Scene/RenderShape/RectRenderShape.cpp
        src/Scene/RenderShape/CircleRenderShape.cpp
        src/Scene/RenderShape/SpriteRenderShape.cpp
        src/Scene/RenderShape/ParticleSystemRenderShape.cpp
        src/Scene/GameObjects/UIObject/Button.cpp)

set(CORE_SOURCES
        src/Core/GameLoop.cpp
        src/Core/SceneManager.cpp
        src/Core/ProjectSettings.cpp)

# Main Project
add_library(${PROJECT_NAME}
        ${SCENE_SOURCES}
        ${SERVICES_SOURCES}
        ${INPUT_SOURCES}
        ${CORE_SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_mixer::SDL2_mixer)
target_link_libraries(${PROJECT_NAME} SDL2_image::SDL2_image)

# Sub Projects
add_subdirectory(tests)
add_subdirectory(validation/US00_Rendering)
