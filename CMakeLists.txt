
cmake_minimum_required(VERSION 3.3)

project(libfreyja C CXX)

set(NANOPB_SRC_ROOT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/nanopb)
set(CMAKE_MODULE_PATH ${NANOPB_SRC_ROOT_FOLDER}/extra)
find_package(Nanopb REQUIRED)
include_directories(${NANOPB_INCLUDE_DIRS})

add_subdirectory(googletest/googletest)

include(common/common.cmake)
include(bootloader/bootloader.cmake)
include(programmer/programmer.cmake)

nanopb_generate_cpp(PROTO_SRCS PROTO_HDRS freyja.proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_custom_target(protobuf DEPENDS ${PROTO_SRCS} ${PROTO_HDRS})
set_source_files_properties(${PROTO_SRCS} ${PROTO_HDRS}
    PROPERTIES GENERATED TRUE)

include_directories(test/include)

add_definitions(-g)

set(TEST_SOURCES
	test/source/Integration.cpp
	test/source/ProgrammerTest.cpp
	test/source/ProtobufTest.cpp
	test/source/main.cpp
	)

add_executable(${CMAKE_PROJECT_NAME}-test ${TEST_SOURCES} ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(${CMAKE_PROJECT_NAME}-test ${LIBS} gtest)

