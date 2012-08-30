cmake_minimum_required( VERSION 2.8 )
project( FWSG-test )

find_package( Boost 1.46 REQUIRED thread unit_test_framework )

if( NOT Boost_USE_STATIC_LIBS )
	add_definitions( -DBOOST_TEST_DYN_LINK )
endif()

set( SRC_DIR "src" )
set( INC_DIR "src" )

set(
	SOURCES
	${INC_DIR}/Window.hpp
	${SRC_DIR}/Test.cpp
	${SRC_DIR}/TestBackfaceCullingState.cpp
	${SRC_DIR}/TestBoolState.cpp
	${SRC_DIR}/TestBufferObject.cpp
	${SRC_DIR}/TestCamera.cpp
	${SRC_DIR}/TestDepthTestState.cpp
	${SRC_DIR}/TestGeometry.cpp
	${SRC_DIR}/TestMatrix.cpp
	${SRC_DIR}/TestNode.cpp
	${SRC_DIR}/TestProgram.cpp
	${SRC_DIR}/TestProgramCommand.cpp
	${SRC_DIR}/TestProgramCommandState.cpp
	${SRC_DIR}/TestRenderState.cpp
	${SRC_DIR}/TestRenderer.cpp
	#${SRC_DIR}/TestStaticMesh.cpp
	${SRC_DIR}/TestStep.cpp
	${SRC_DIR}/TestStepProxy.cpp
	${SRC_DIR}/TestTextureState.cpp
	${SRC_DIR}/TestTransform.cpp
	${SRC_DIR}/TestTriangleGeometry.cpp
	${SRC_DIR}/TestUniformValue.cpp
	${SRC_DIR}/TestVertex.cpp
	${SRC_DIR}/TestWireframeState.cpp
	${SRC_DIR}/Window.cpp
)

include_directories( ${PROJECT_SOURCE_DIR}/../include )
include_directories( ${Boost_INCLUDE_DIRS} )

add_executable( test ${SOURCES} )

target_link_libraries( test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
target_link_libraries( test ${Boost_THREAD_LIBRARY} )
target_link_libraries( test fwsg )

add_custom_command(
	TARGET test
	COMMAND test
	WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
