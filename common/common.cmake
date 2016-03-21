
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(COMMON_SOURCES
	
)

add_library(common ${COMMON_SOURCES})

set(LIBS ${LIBS} common)
