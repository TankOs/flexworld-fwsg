cmake_minimum_required( VERSION 2.8 )
project( FWSG )

set( FWSG_BUILD_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries." )
set( FWSG_BUILD_TEST TRUE CACHE BOOL "Build test suite." )
set( FWSG_BUILD_EXAMPLES FALSE CACHE BOOL "Build examples." )
set( FWSG_BUILD_DOCS FALSE CACHE BOOL "Build Doxygen API documentation." )
set( SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Was SFML built as a static library?" )

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Build type." FORCE )
endif()

find_package( FWU REQUIRED )
find_package( SFML 2.0 REQUIRED GRAPHICS WINDOW SYSTEM )

find_package( GLEW REQUIRED )
find_package( OPENGL REQUIRED )
	
if( FWSG_BUILD_SHARED_LIBS )
	set( LIB_TYPE SHARED )
else()
	set( LIB_TYPE STATIC )
endif()

if( CMAKE_COMPILER_IS_GNUCXX )
	if( NOT CMAKE_CXX_FLAGS )
		set( CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Wconversion -pedantic" CACHE STRING "C++ compiler flags." FORCE )
	endif()
endif()

set( SRC_DIR "src" )
set( INC_DIR "include" )

set(
	SOURCES
	${INC_DIR}/FWSG/BackfaceCullingState.hpp
	${INC_DIR}/FWSG/BoolState.hpp
	${INC_DIR}/FWSG/BufferObject.hpp
	${INC_DIR}/FWSG/Camera.hpp
	${INC_DIR}/FWSG/DepthTestState.hpp
	${INC_DIR}/FWSG/Drawable.hpp
	${INC_DIR}/FWSG/Geometry.hpp
	${INC_DIR}/FWSG/Node.hpp
	${INC_DIR}/FWSG/Node.inl
	${INC_DIR}/FWSG/Program.hpp
	${INC_DIR}/FWSG/ProgramCommand.hpp
	${INC_DIR}/FWSG/ProgramCommandState.hpp
	${INC_DIR}/FWSG/RenderState.hpp
	${INC_DIR}/FWSG/Renderer.hpp
	${INC_DIR}/FWSG/State.hpp
	${INC_DIR}/FWSG/StaticMesh.hpp
	${INC_DIR}/FWSG/Step.hpp
	${INC_DIR}/FWSG/StepProxy.hpp
	${INC_DIR}/FWSG/TextureState.hpp
	${INC_DIR}/FWSG/Transform.hpp
	${INC_DIR}/FWSG/TriangleGeometry.hpp
	${INC_DIR}/FWSG/Uniform1fValue.hpp
	${INC_DIR}/FWSG/Uniform2fValue.hpp
	${INC_DIR}/FWSG/Uniform3fValue.hpp
	${INC_DIR}/FWSG/Uniform4fValue.hpp
	${INC_DIR}/FWSG/UniformValue.hpp
	${INC_DIR}/FWSG/Vertex.hpp
	${INC_DIR}/FWSG/WireframeState.hpp
	${SRC_DIR}/FWSG/BackfaceCullingState.cpp
	${SRC_DIR}/FWSG/BoolState.cpp
	${SRC_DIR}/FWSG/BufferObject.cpp
	${SRC_DIR}/FWSG/Camera.cpp
	${SRC_DIR}/FWSG/DepthTestState.cpp
	${SRC_DIR}/FWSG/Drawable.cpp
	${SRC_DIR}/FWSG/Geometry.cpp
	${SRC_DIR}/FWSG/Node.cpp
	${SRC_DIR}/FWSG/Program.cpp
	${SRC_DIR}/FWSG/ProgramCommand.cpp
	${SRC_DIR}/FWSG/ProgramCommandState.cpp
	${SRC_DIR}/FWSG/RenderState.cpp
	${SRC_DIR}/FWSG/Renderer.cpp
	${SRC_DIR}/FWSG/State.cpp
	${SRC_DIR}/FWSG/StaticMesh.cpp
	${SRC_DIR}/FWSG/Step.cpp
	${SRC_DIR}/FWSG/StepProxy.cpp
	${SRC_DIR}/FWSG/TextureState.cpp
	${SRC_DIR}/FWSG/Transform.cpp
	${SRC_DIR}/FWSG/TriangleGeometry.cpp
	${SRC_DIR}/FWSG/Uniform1fValue.cpp
	${SRC_DIR}/FWSG/Uniform2fValue.cpp
	${SRC_DIR}/FWSG/Uniform3fValue.cpp
	${SRC_DIR}/FWSG/Uniform4fValue.cpp
	${SRC_DIR}/FWSG/UniformValue.cpp
	${SRC_DIR}/FWSG/Vertex.cpp
	${SRC_DIR}/FWSG/WireframeState.cpp
)

include_directories( ${INC_DIR} )
include_directories( ${GLEW_INCLUDE_DIR} )
include_directories( ${SFML_INCLUDE_DIR} )
include_directories( ${FWU_INCLUDE_DIR} )

add_library( fwsg ${LIB_TYPE} ${SOURCES} )

target_link_libraries( fwsg ${GLEW_LIBRARY} )
target_link_libraries( fwsg ${OPENGL_LIBRARY} )
target_link_libraries( fwsg ${SFML_GRAPHICS_LIBRARY} )
target_link_libraries( fwsg ${SFML_WINDOW_LIBRARY} )
target_link_libraries( fwsg ${SFML_SYSTEM_LIBRARY} )

if( NOT FWSG_SKIP_INSTALL )
	install(
		TARGETS fwsg
		RUNTIME DESTINATION bin COMPONENT bin
		LIBRARY DESTINATION lib COMPONENT bin
		ARCHIVE DESTINATION lib COMPONENT dev
	)

	install(
		DIRECTORY include/FWSG
		DESTINATION include
	)
endif()

if( FWSG_BUILD_EXAMPLES )
	add_subdirectory( examples )
endif()

if( FWSG_BUILD_TEST )
	add_subdirectory( test )
endif()

if( FWSG_BUILD_DOCS )
	add_subdirectory( "doc/doxygen" )
endif()
