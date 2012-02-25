cmake_minimum_required( VERSION 2.8 )

find_package( SFML 2.0 REQUIRED GRAPHICS WINDOW SYSTEM )

macro( BUILD_EXAMPLE target sources )
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

BUILD_EXAMPLE( helloworld HelloWorld.cpp )
