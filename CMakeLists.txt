cmake_minimum_required(VERSION 3.2.2)
project(ccArray)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/Array.cpp)
add_library(ccArray ${SOURCE_FILES})

add_executable(examples_simple examples/simple.cpp)
target_link_libraries(examples_simple ccArray)
find_package(GTest REQUIRED)

if (GTEST_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(runTests test/simple.cpp)
    target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ccArray)
endif(GTEST_FOUND)