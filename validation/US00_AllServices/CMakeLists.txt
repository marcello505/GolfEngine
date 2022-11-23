cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES main.cpp SceneFactory.cpp MovementScript.cpp MovementScript.h)

# Main Project
add_executable(POC_Test_All_Services ${SRC_FILES})
target_link_libraries(POC_Test_All_Services GolfEngine)
