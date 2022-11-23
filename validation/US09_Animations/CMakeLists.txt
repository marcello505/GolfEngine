cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES SceneFactory.cpp)

# Main Project
add_executable(SpriteAnimation_Demo main.cpp ${SRC_FILES})
target_link_libraries(SpriteAnimation_Demo GolfEngine)
target_include_directories(SpriteAnimation_Demo PUBLIC ../../src)

