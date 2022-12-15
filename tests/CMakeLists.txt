cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(TEST_SOURCES
        LibSDL2ImageTests.cpp
        LibSDL2MixerTests.cpp
        LibSDL2Tests.cpp
        Core/GameLoopTests.cpp
        Core/ProjectSettingsTests.cpp
        libSDL2TtfTest.cpp
        Services/Box2DPhysicsService.cpp)

set(SCENE_TEST_SOURCES
        Scene/SceneTests.cpp
        Scene/GameObjectTests.cpp
        Scene/Components/AudioSourceTests.cpp
        Scene/PersistableTests.cpp)

set(UTILITIES_TEST_SOURCES
        Utilities/RandomTests.cpp)

# Main Project
add_executable(Golf_Tests main.cpp
        ${TEST_SOURCES}
        ${SCENE_TEST_SOURCES}
        ${UTILITIES_TEST_SOURCES})

target_link_libraries(Golf_Tests GolfEngine)
target_include_directories(Golf_Tests PUBLIC ../libs/doctest)
target_include_directories(Golf_Tests PUBLIC ../src)
