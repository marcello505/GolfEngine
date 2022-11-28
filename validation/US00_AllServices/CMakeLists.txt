cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES main.cpp SceneFactory.cpp MovementScript.cpp MovementScript.h)

# Project Resources
add_custom_target(POC_Test_All_Services_Res ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)

# Main Project
add_executable(POC_Test_All_Services ${SRC_FILES})
target_link_libraries(POC_Test_All_Services GolfEngine)
add_dependencies(POC_Test_All_Services POC_Test_All_Services_Res)
