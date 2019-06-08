cmake_minimum_required(VERSION 3.14)
project(cpp)

set(CMAKE_CXX_STANDARD 17)

# my includes
include_directories("include")

# my source files
file(GLOB TEST_SOURCE_FILES "tests/*.cpp")
file(GLOB MATH_TEST_SOURCE_FILES "tests/math/*.cpp")
set(SOURCE_FILES main.cpp ${TEST_SOURCE_FILES} ${MATH_TEST_SOURCE_FILES})
add_executable(cpp ${SOURCE_FILES})

# google test
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
target_link_libraries(cpp gtest gtest_main)
