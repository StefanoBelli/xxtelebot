cmake_minimum_required(VERSION 2.8)

include_directories(${HEADERS_DIR})

set(CMAKE_CXX_STANDARD 11)
set(SOURCES "main.cpp")

if (NOT CMAKE_PREFIX_DIR AND UNIX)
	message("-- Probing prefix directory...")
	if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
		set(CMAKE_PREFIX_DIR "/usr")
	else ()
		set(CMAKE_PREFIX_DIR "/usr/local")
	endif ()
	message("-- CMAKE_PREFIX_DIR=${CMAKE_PREFIX_DIR}")
endif ()

if(LIBRARY_TYPE STREQUAL "static")
	add_library(tgbot STATIC ${SOURCES})
	
	install(TARGETS tgbot ARCHIVE
				DESTINATION ${CMAKE_PREFIX_DIR}/lib
				PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE
				GROUP_WRITE GROUP_READ)
else()
	add_library(tgbot SHARED ${SOURCES})
	
	install(TARGETS tgbot LIBRARY
				DESTINATION ${CMAKE_PREFIX_DIR}/lib
				PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE
				GROUP_WRITE GROUP_READ)
endif()

install(DIRECTORY "${HEADERS_DIR}/tgbot"
				DESTINATION "${CMAKE_PREFIX_DIR}/include"
				FILE_PERMISSIONS OWNER_WRITE OWNER_READ
				GROUP_WRITE GROUP_READ)
