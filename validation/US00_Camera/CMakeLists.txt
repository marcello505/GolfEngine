cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES)

# Resource files
add_custom_target(POC_US00_Camera_res ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)

# Main Project
add_executable(POC_US00_Camera main.cpp)
add_dependencies(POC_US00_Camera POC_US00_Camera_res)
target_link_libraries(POC_US00_Camera GolfEngine)
