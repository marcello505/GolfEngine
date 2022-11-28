cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources

# Resource files
add_custom_target(Game_Resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)

# Main Project
add_executable(Game
        main.cpp)
target_link_libraries(Game GolfEngine)
add_dependencies(Game Game_Resources)
