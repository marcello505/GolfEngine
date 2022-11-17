cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES)

# Main Project
add_executable(RenderFPS_PoC main.cpp RectDrawable.cpp RectDrawable.h TextDrawable.cpp TextDrawable.h)
target_link_libraries(RenderFPS_PoC GolfEngine)
target_include_directories(RenderFPS_PoC PUBLIC ../../src)
