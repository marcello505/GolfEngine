cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES)

# Main Project
add_executable(InputService_PoC main.cpp)
target_link_libraries(InputService_PoC GolfEngine)
target_include_directories(InputService_PoC PUBLIC ../../src)
