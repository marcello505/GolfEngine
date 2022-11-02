cmake_minimum_required(VERSION 3.23)

# ENV setup
set(CMAKE_CXX_STANDARD 17)

# Sources
set(TEST_SOURCES SampleTests.cpp)

# Main Project
add_executable(Golf_Tests main.cpp
        ${TEST_SOURCES}
        )
target_include_directories(Golf_Tests PUBLIC ../libs/doctest)
target_include_directories(Golf_Tests PUBLIC ../src)
