
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(PROGRAMMER_SOURCES
	
)

add_library(programmer ${PROGRAMMER_SOURCES})

set(LIBS ${LIBS} programmer)
