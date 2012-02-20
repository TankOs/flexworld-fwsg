cmake_minimum_required( VERSION 2.8 )
project( FWSG )

find_package( SFML 2.0 REQUIRED GRAPHICS WINDOW )

set( FWSG_BUILD_SHARED_LIBS FALSE CACHE BOOL "Build shared libraries." )
set( FWSG_BUILD_TEST FALSE CACHE BOOL "Build test suite." )

if( FWSG_BUILD_SHARED_LIBS )
	set( LIB_TYPE SHARED )
else()
	set( LIB_TYPE STATIC )
endif()

if( CMAKE_COMPILER_IS_GNUCXX )
	if( NOT CMAKE_CXX_FLAGS )
		set( CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -Wshadow -Wconversion -pedantic" CACHE STRING "C++ compiler flags." FORCE )
	endif()
endif()

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Build type." FORCE )
endif()

set( SRC_DIR "src" )
set( INC_DIR "include" )

set(
	SOURCES
	${INC_DIR}/FWSG/BufferObject.hpp
	${INC_DIR}/FWSG/NonCopyable.hpp
	${INC_DIR}/FWSG/Step.hpp
	${INC_DIR}/FWSG/Vertex.hpp
	${SRC_DIR}/FWSG/BufferObject.cpp
	${SRC_DIR}/FWSG/NonCopyable.cpp
	${SRC_DIR}/FWSG/Step.cpp
	${SRC_DIR}/FWSG/Vertex.cpp
)

include_directories( ${INC_DIR} )
include_directories( ${SFML_INCLUDE_DIR} )

add_library( fwsg ${LIB_TYPE} ${SOURCES} )

target_link_libraries( fwsg ${SFML_GRAPHICS_LIBRARY} )
target_link_libraries( fwsg ${SFML_WINDOW_LIBRARY} )

if( FWSG_BUILD_TEST )
	add_subdirectory( test )
endif()
