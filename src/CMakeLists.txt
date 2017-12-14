cmake_minimum_required(VERSION 2.8)

include_directories(${HEADERS_DIR} ${OTHER_HDR_DIR})

find_package(CURL REQUIRED)
find_library(JSONCPP "jsoncpp")

if(JSONCPP)
	message("-- Found JsonCpp: ${JSONCPP}")
else()
	message(FATAL_ERROR "!! Cannot find JsonCpp")
endif()

set(CMAKE_CXX_STANDARD 11)
set(SOURCES https.cpp bot.cpp api.cpp api_types.cpp types.cpp encode.cpp)

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
				GROUP_WRITE GROUP_READ
				WORLD_READ)
else()
	add_library(tgbot SHARED ${SOURCES})
	
	install(TARGETS tgbot LIBRARY
				DESTINATION ${CMAKE_PREFIX_DIR}/lib
				PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE
				GROUP_WRITE GROUP_READ
				WORLD_READ)
endif()

target_link_libraries(tgbot ${CURL_LIBRARIES} ${JSONCPP})

install(DIRECTORY "${HEADERS_DIR}/tgbot"
				DESTINATION "${CMAKE_PREFIX_DIR}/include"
				FILE_PERMISSIONS OWNER_WRITE OWNER_READ
				GROUP_WRITE GROUP_READ
				WORLD_READ)
