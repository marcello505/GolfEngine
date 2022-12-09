cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES)

# Main Project
add_executable(POC_US00_Camera main.cpp)
target_link_libraries(POC_US00_Camera GolfEngine)
