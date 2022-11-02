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

set(INPUT_SOURCES
        src/Input/Action.h
        src/Input/ActionMap.cpp
        src/Input/ActionMap.h
        src/Input/InputKey.h)

#Source Files
set(SERVICES_SOURCES
        src/Services/Box2DPhysicsService.cpp
        src/Services/SDLAudioService.cpp
        src/Services/SDLRenderService.cpp
        src/Services/SDLInputService.cpp)
set(SCENE_SOURCES
        src/Scene/Scene.cpp
        src/Scene/GameObject.cpp)

set(CORE_SOURCES
        src/Core/GameLoop.cpp
        src/Core/GameLoop.h
        src/Core/SceneManager.cpp
        src/Core/SceneManager.h
        src/Core/ProjectSettings.cpp
        src/Core/ProjectSettings.h)
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
