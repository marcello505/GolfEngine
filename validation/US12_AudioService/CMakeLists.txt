cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES)

# Resource files
add_custom_target(POC_US12_AudioService_Deps ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)

# Main Project
add_executable(AudioService_PoC main.cpp)
target_link_libraries(AudioService_PoC GolfEngine)
target_include_directories(AudioService_PoC PUBLIC ../../src)
add_dependencies(AudioService_PoC POC_US12_AudioService_Deps)