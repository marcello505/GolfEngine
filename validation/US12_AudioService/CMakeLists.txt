cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES)

# Resource files
add_custom_target(POC_US12_AudioService_Deps ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)

# Main Project
add_executable(POC_US12_AudioService main.cpp)
target_link_libraries(POC_US12_AudioService GolfEngine)
target_include_directories(POC_US12_AudioService PUBLIC ../../src)
add_dependencies(POC_US12_AudioService POC_US12_AudioService_Deps)