
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(BOOTLOADER_SOURCES
	${CMAKE_CURRENT_LIST_DIR}/source/Bootloader.cpp
)

add_library(bootloader ${BOOTLOADER_SOURCES})

set(LIBS ${LIBS} bootloader)
