cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(SRC_FILES main.cpp SceneFactory.cpp)

# Main Project
add_executable(Particles_US101 ${SRC_FILES})
target_link_libraries(Particles_US101 GolfEngine)
