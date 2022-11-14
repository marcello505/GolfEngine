cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES)

# Main Project
add_executable(AudioService_PoC main.cpp)
target_link_libraries(AudioService_PoC GolfEngine)
target_include_directories(AudioService_PoC PUBLIC ../../src)
