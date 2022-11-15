cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(TEST_SOURCES
        LibSDL2ImageTests.cpp
        LibSDL2MixerTests.cpp
        LibSDL2Tests.cpp
        Core/GameLoopTests.cpp)

set(SCENE_TEST_SOURCES
        Scene/SceneTests.cpp
        Scene/GameObjectTests.cpp)


# Main Project
add_executable(Golf_Tests main.cpp
        ${TEST_SOURCES}
        ${SCENE_TEST_SOURCES})

target_link_libraries(Golf_Tests GolfEngine)
target_include_directories(Golf_Tests PUBLIC ../libs/doctest)
target_include_directories(Golf_Tests PUBLIC ../src)
