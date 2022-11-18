cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES RectDrawable.cpp LineDrawable.cpp SpriteDrawable.cpp CircleDrawable.cpp CircleDrawable.h)

# Main Project
add_executable(Rendering_Demo main.cpp ${SRC_FILES})
target_link_libraries(Rendering_Demo GolfEngine)
target_link_libraries(Rendering_Demo SDL2_image::SDL2_image)
target_include_directories(Rendering_Demo PUBLIC ../../src)

