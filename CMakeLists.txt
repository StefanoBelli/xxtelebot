cmake_minimum_required(VERSION 2.8)

project(TelegramBotApi CXX)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

#version
set(MJVER 0)
set(MNVER 0)
set(PTVER 0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

set(HEADERS_DIR "${CMAKE_SOURCE_DIR}/include")

if(NOT CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	
	message(FATAL_ERROR "!! Compiler identification: ${CMAKE_CXX_COMPILER_ID} is not supported")

endif()

if(NOT LIBRARY_TYPE)
	set(LIBRARY_TYPE "static")
endif()

find_program(DOXYGEN_EXISTS "doxygen")
if(DOXYGEN_EXISTS)
	add_custom_target(docs doxygen Doxyfile
			DEPENDS "include/tgbot/version.h"
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

	message("-- Doxygen is available, use 'make docs' to generate docs")
endif ()

configure_file("${HEADERS_DIR}/tgbot/version.h.in"
	"${HEADERS_DIR}/tgbot/version.h")

add_subdirectory(src)
