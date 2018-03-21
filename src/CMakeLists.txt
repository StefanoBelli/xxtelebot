cmake_minimum_required(VERSION 3.2)

include_directories(${HEADERS_DIR} ${OTHER_HEADERS_DIR})

find_package(CURL REQUIRED)
find_library(JSONCPP "jsoncpp")

if(JSONCPP)
	message("-- Found JsonCpp: ${JSONCPP}")
else()
	message(FATAL_ERROR "!! Cannot find JsonCpp")
endif()

set(CMAKE_CXX_STANDARD 11)
set(SOURCES https.cpp bot.cpp api.cpp api_types.cpp types.cpp encode.cpp)

add_library(tgbot ${SOURCES})
target_link_libraries(tgbot ${CURL_LIBRARIES} ${JSONCPP})
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
