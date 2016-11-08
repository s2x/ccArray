cmake_minimum_required(VERSION 3.2.2)
project(ccArray)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 1)
set(LIB_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} )

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/Array.cpp src/helpers/ArrayHelper.cpp)

add_library(ccArrayShared SHARED ${SOURCE_FILES})
add_library(ccArrayStatic STATIC ${SOURCE_FILES})
set_target_properties(ccArrayShared PROPERTIES OUTPUT_NAME ccarray)
set_target_properties(ccArrayStatic PROPERTIES OUTPUT_NAME ccarray)

set_target_properties(ccArrayShared PROPERTIES VERSION ${LIB_VERSION} SOVERSION ${VERSION_MAJOR} )

add_executable(examples_simple examples/simple.cpp)
target_link_libraries(examples_simple ccArrayStatic)

find_package(GTest)
if (GTEST_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(runTests test/simple.cpp)
    target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ccArray)
    add_test(runTests runTests)

    if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
        include(CodeCoverage)
        setup_target_for_coverage(ccArray_coverage runTests coverage)

        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    endif()

endif(GTEST_FOUND)

install(TARGETS ccArrayShared DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(TARGETS ccArrayStatic DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(DIRECTORY include DESTINATION ${CMAKE_INSTALL_PREFIX} FILES_MATCHING PATTERN "*")

