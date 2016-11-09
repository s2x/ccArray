if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	    MESSAGE(FATAL_ERROR "Prevented in-tree built. This is bad practice.")
endif()

cmake_minimum_required(VERSION 3.2.2)
project(ccArray)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 1)
set(LIB_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} )

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/Array.cpp src/helpers/ArrayHelper.cpp)

set(JSMN_SOURCE ${CMAKE_SOURCE_DIR}/vendor/jsmn/jsmn.h)

if(NOT EXISTS ${JSMN_SOURCE})
    execute_process(COMMAND git submodule update --init -- vendor/jsmn
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
else()
    set(JSMN_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/vendor/jsmn/libjsmn.a)
    add_custom_target(build_jsmn ALL
            COMMAND make
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/vendor/jsmn/
            COMMENT "Building jsmn")

    add_library(jsmn STATIC IMPORTED)
    set_property(TARGET jsmn APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
    set_target_properties(jsmn PROPERTIES IMPORTED_LOCATION_NOCONFIG "${JSMN_LIBRARY}")
    add_dependencies(jsmn build_jsmn)
endif()

add_library(ccArrayShared SHARED ${SOURCE_FILES})
add_library(ccArrayStatic STATIC ${SOURCE_FILES})

target_link_libraries(ccArrayShared jsmn)
target_link_libraries(ccArrayStatic jsmn)

set_target_properties(ccArrayShared PROPERTIES OUTPUT_NAME ccarray)
set_target_properties(ccArrayStatic PROPERTIES OUTPUT_NAME ccarray)

set_target_properties(ccArrayShared PROPERTIES VERSION ${LIB_VERSION} SOVERSION ${VERSION_MAJOR} )

add_executable(examples_simple examples/simple.cpp)
target_link_libraries(examples_simple ccArrayStatic jsmn)

find_package(GTest)
if (GTEST_FOUND)
    enable_testing()
    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(runTests test/simple.cpp)
    target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ccArrayStatic jsmn)
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

