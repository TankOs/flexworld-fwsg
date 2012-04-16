cmake_minimum_required( VERSION 2.8 )

find_package( SFML 2.0 REQUIRED GRAPHICS WINDOW SYSTEM )

macro( build_example target sources )
	include_directories( ${PROJECT_SOURCE_DIR}/../include/ )
	include_directories( ${SFML_INCLUDE_DIR}/../include/ )

	add_executable( ${target} ${sources} )

	target_link_libraries( ${target} fwsg )
	target_link_libraries( ${target} ${SFML_GRAPHICS_LIBRARY} )
	target_link_libraries( ${target} ${SFML_WINDOW_LIBRARY} )
	target_link_libraries( ${target} ${SFML_SYSTEM_LIBRARY} )

	install(
		TARGETS ${target}
		DESTINATION share/FWSG/examples
	)
endmacro()

build_example( helloworld HelloWorld.cpp )
build_example( texture Texture.cpp )
build_example( transform Transform.cpp )
build_example( depthtest DepthTest.cpp )
build_example( colors Colors.cpp )
#build_example( shader Shader.cpp )
