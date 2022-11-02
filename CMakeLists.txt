cmake_minimum_required(VERSION 3.23)
project(GolfEngine)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Package paths
if(WIN32)
    #Windows specific packages
    set(SDL2_DIR libs/sdl2/cmake)
    set(SDL2_MIXER_DIR libs/sdl_mixer/cmake)
endif()
set(IMGUI_DIR libs/imgui/cmake)

# Packages
find_package(SDL2 REQUIRED)
find_package(IMGUI REQUIRED)
find_package(SDL2_MIXER REQUIRED)

# Includes
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${IMGUI_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

#Source Files
set(SCENE_SOURCES
        src/Scene/Scene.cpp
        src/Scene/GameObject.cpp src/Scene/AudioSource.cpp src/Scene/Component.cpp src/Scene/BehaviourScript.cpp src/Scene/Drawable.cpp src/Scene/Animator.cpp src/Scene/ParticleSystem.cpp src/Scene/Pathfinding.cpp)

# Main Project
add_library(${PROJECT_NAME}
        ${SCENE_SOURCES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_MIXER_LIBRARIES})


# Sub Projects
add_subdirectory(tests)
