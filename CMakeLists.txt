cmake_minimum_required( VERSION 2.8 )
project( FWSG )

find_package( SFML 2.0 REQUIRED GRAPHICS WINDOW SYSTEM )

set( FWSG_BUILD_SHARED_LIBS FALSE CACHE BOOL "Build shared libraries." )
set( FWSG_BUILD_TEST FALSE CACHE BOOL "Build test suite." )
set( FWSG_BUILD_EXAMPLES FALSE CACHE BOOL "Build examples." )

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
	${INC_DIR}/FWSG/BackfaceCullingState.hpp
	${INC_DIR}/FWSG/BoolState.hpp
	${INC_DIR}/FWSG/BufferObject.hpp
	${INC_DIR}/FWSG/Drawable.hpp
	${INC_DIR}/FWSG/Geometry.hpp
	${INC_DIR}/FWSG/Leaf.hpp
	${INC_DIR}/FWSG/Leaf.inl
	${INC_DIR}/FWSG/Node.hpp
	${INC_DIR}/FWSG/NonCopyable.hpp
	${INC_DIR}/FWSG/RenderState.hpp
	${INC_DIR}/FWSG/Renderer.hpp
	${INC_DIR}/FWSG/State.hpp
	${INC_DIR}/FWSG/StaticMesh.hpp
	${INC_DIR}/FWSG/Step.hpp
	${INC_DIR}/FWSG/StepProxy.hpp
	${INC_DIR}/FWSG/TextureState.hpp
	${INC_DIR}/FWSG/Transform.hpp
	${INC_DIR}/FWSG/TriangleGeometry.hpp
	${INC_DIR}/FWSG/Vertex.hpp
	${INC_DIR}/FWSG/WireframeState.hpp
	${SRC_DIR}/FWSG/BackfaceCullingState.cpp
	${SRC_DIR}/FWSG/BoolState.cpp
	${SRC_DIR}/FWSG/BufferObject.cpp
	${SRC_DIR}/FWSG/Drawable.cpp
	${SRC_DIR}/FWSG/Geometry.cpp
	${SRC_DIR}/FWSG/Leaf.cpp
	${SRC_DIR}/FWSG/Node.cpp
	${SRC_DIR}/FWSG/NonCopyable.cpp
	${SRC_DIR}/FWSG/RenderState.cpp
	${SRC_DIR}/FWSG/Renderer.cpp
	${SRC_DIR}/FWSG/State.cpp
	${SRC_DIR}/FWSG/StaticMesh.cpp
	${SRC_DIR}/FWSG/Step.cpp
	${SRC_DIR}/FWSG/StepProxy.cpp
	${SRC_DIR}/FWSG/TextureState.cpp
	${SRC_DIR}/FWSG/Transform.cpp
	${SRC_DIR}/FWSG/TriangleGeometry.cpp
	${SRC_DIR}/FWSG/Vertex.cpp
	${SRC_DIR}/FWSG/WireframeState.cpp
)

include_directories( ${INC_DIR} )
include_directories( ${SFML_INCLUDE_DIR} )

add_library( fwsg ${LIB_TYPE} ${SOURCES} )

target_link_libraries( fwsg ${SFML_GRAPHICS_LIBRARY} )
target_link_libraries( fwsg ${SFML_WINDOW_LIBRARY} )
target_link_libraries( fwsg ${SFML_SYSTEM_LIBRARY} )

install(
	TARGETS fwsg
	RUNTIME DESTINATION bin COMPONENT bin
	LIBRARY DESTINATION lib COMPONENT bin
	ARCHIVE DESTINATION lib COMPONENT dev
)

if( FWSG_BUILD_EXAMPLES )
	add_subdirectory( examples )
endif()

if( FWSG_BUILD_TEST )
	add_subdirectory( test )
endif()
