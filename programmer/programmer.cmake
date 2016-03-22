
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(PROGRAMMER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/source/Application.cpp
	${CMAKE_CURRENT_LIST_DIR}/source/Programmer.cpp
)

add_library(programmer ${PROGRAMMER_SOURCES})

set(LIBS ${LIBS} programmer)
