#
# Find FWSG library.
#
# Input variables:
#   FWSG_ROOT              Additional library search directory.
#   FWSG_STATIC_LIBRARIES  Look for static libraries.
#
# Output variables:
#   FWSG_INCLUDE_DIR   Include directory.
#   FWSG_LIBRARY       Library.

cmake_minimum_required( VERSION 2.8 )

set( FWSG_FOUND FALSE )

if( FWSG_STATIC_LIBRARIES )
	set( FWSG_SUFFIX "-s" )
	add_definitions( -DFWSG_STATIC )
else()
	set( FWSG_SUFFIX "" )
endif()

find_path(
	FWSG_INCLUDE_DIR
	FWSG/Renderer.hpp
	PATH_SUFFIXES
		include
	PATHS
		/usr
		/usr/local
		${FWSG_ROOT}
)

find_library(
	FWSG_LIBRARY_RELEASE
	FWSG${FWSG_SUFFIX}
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${FWSG_ROOT}
)

find_library(
	FWSG_LIBRARY_DEBUG
	fwsg${FWSG_SUFFIX}-d
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${FWSG_ROOT}
)

if( FWSG_LIBRARY_RELEASE AND FWSG_LIBRARY_DEBUG )
	set( FWSG_LIBRARY debug ${FWSG_LIBRARY_DEBUG} optimized ${FWSG_LIBRARY_RELEASE} )
elseif( FWSG_LIBRARY_RELEASE )
	set( FWSG_LIBRARY ${FWSG_LIBRARY_RELEASE} )
elseif( FWSG_LIBRARY_DEBUG )
	set( FWSG_LIBRARY ${FWSG_LIBRARY_DEBUG} )
endif()

if( NOT FWSG_INCLUDE_DIR OR NOT FWSG_LIBRARY )
	message( FATAL_ERROR "FWSG not found." )
else()
	message( "FWSG found: ${FWSG_INCLUDE_DIR}" )
endif()
