
cmake_minimum_required(VERSION 3.3)

project(fifteen-four C CXX)

add_subdirectory(googletest/googletest)

include(common/common.cmake)
include(bootloader/bootloader.cmake)
include(programmer/programmer.cmake)

include_directories(test/include)

add_definitions(-g)

set(TEST_SOURCES
	test/source/main.cpp
	)

add_executable(${CMAKE_PROJECT_NAME} ${TEST_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} fifteenfour gtest)

