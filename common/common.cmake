
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(COMMON_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/source/Version.cpp
	${CMAKE_CURRENT_LIST_DIR}/source/Serializer.cpp
)

add_library(common ${COMMON_SOURCES})

set(LIBS ${LIBS} common)
