cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)


# Sources
set(SRC_FILES main.cpp SceneFactory.cpp ../US00_Rendering/RectDrawable.cpp DrawPathScript.cpp MovementScript.cpp)


# Main Project
add_executable(RenderAIObject_PoC ${SRC_FILES})
target_link_libraries(RenderAIObject_PoC GolfEngine)
target_include_directories(RenderAIObject_PoC PUBLIC ../../src)
