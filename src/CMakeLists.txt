cmake_minimum_required(VERSION 3.2)

find_package(PkgConfig)
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)
find_library(GCRYPT_LIBRARY NAMES gcrypt libgcrypt)

pkg_check_modules(JSONCPP QUIET jsoncpp)

if(NOT GCRYPT_LIBRARY)
	message(FATAL_ERROR "Could not find gcrypt library")
endif()

if(JSONCPP_LIBRARIES)
	message(STATUS "Found JsonCpp: ${JSONCPP_LIBRARIES}")
	if(NOT JSONCPP_INCLUDE_DIRS STREQUAL "")
		message(STATUS "Found JsonCpp headers: ${JSONCPP_INCLUDE_DIRS}")
		include_directories("${JSONCPP_INCLUDE_DIRS}")
	endif()
else()
	message(FATAL_ERROR "!! Cannot find JsonCpp")
endif()

set(CMAKE_CXX_STANDARD 11)
set(SOURCES time.cpp logger.cpp https.cpp bot.cpp api.cpp api_types.cpp types.cpp encode.cpp)

add_library(tgbot ${SOURCES})
target_link_libraries(tgbot 
	PRIVATE 
		${CURL_LIBRARIES} 
		${JSONCPP_LIBRARIES}
		${GCRYPT_LIBRARY}
		Threads::Threads
)

target_include_directories(tgbot 
	PUBLIC ${HEADERS_DIR}
)

set_property(TARGET tgbot
	PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS tgbot
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE
	GROUP_WRITE GROUP_READ
	WORLD_READ)

install(DIRECTORY "${HEADERS_DIR}/tgbot"
	DESTINATION include
	FILE_PERMISSIONS OWNER_WRITE OWNER_READ
	GROUP_WRITE GROUP_READ
	WORLD_READ)
