#include "Window.hpp"

#include <GL/glew.h>

#include <FWSG/Program.hpp>

#include <SFML/Window.hpp>
#include <boost/test/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_CASE( TestProgram ) {
	init_test_window();

	// Initial state.
	{
		sg::Program program;

		BOOST_CHECK( program.is_linked() == false );
		BOOST_CHECK( program.get_num_shaders() == 0 );
		BOOST_CHECK( program.get_num_uniforms() == 0 );
	}

	// Add shaders.
	{
		const std::string VALID_SOURCE = "void main() {}";
		const std::string INVALID_SOURCE = "void main() { ljs fot4 w5 vg94e8ehg riugh }";

		sg::Program program;

		BOOST_CHECK( program.add_shader( VALID_SOURCE, sg::Program::VERTEX_SHADER ) == true );
		BOOST_CHECK( program.add_shader( INVALID_SOURCE, sg::Program::VERTEX_SHADER ) == false );

		BOOST_CHECK( program.add_shader( VALID_SOURCE, sg::Program::FRAGMENT_SHADER ) == true );
		BOOST_CHECK( program.add_shader( INVALID_SOURCE, sg::Program::FRAGMENT_SHADER ) == false );

		BOOST_CHECK( program.get_num_shaders() == 2 );
	}

	// Link program.
	{
		const std::string VERTEX_SOURCE = "void main() { gl_Position = ftransform(); }";
		const std::string FRAGMENT_SOURCE = "void main() { gl_FragColor = gl_Color; }";

		sg::Program program;

		// Check linking without any shaders fails.
		BOOST_CHECK( program.get_num_shaders() == 0 );
		BOOST_CHECK( program.link() == false );
		BOOST_CHECK( program.is_linked() == false );

		// Add shaders.
		BOOST_CHECK( program.add_shader( VERTEX_SOURCE, sg::Program::VERTEX_SHADER ) == true );
		BOOST_CHECK( program.add_shader( FRAGMENT_SOURCE, sg::Program::FRAGMENT_SHADER ) == true );
		BOOST_CHECK( program.get_num_shaders() == 2 );

		// Link.
		BOOST_CHECK( program.link() == true );
		BOOST_CHECK( program.is_linked() == true );

		// Add another shader to check if the program gets reset.
		BOOST_CHECK( program.add_shader( VERTEX_SOURCE, sg::Program::VERTEX_SHADER ) == true );
		BOOST_CHECK( program.is_linked() == false );
	}

	// Uniforms.
	{
		const std::string VERTEX_SOURCE = "uniform float var0; void main() { gl_Position = vec4( var0, var0, var0, var0 ); }";
		const std::string FRAGMENT_SOURCE = "uniform float var1; void main() { gl_FragColor = vec4( var1, var1, var1, var1 ); }";

		sg::Program program;

		// Try to register uniform without linked program.
		BOOST_CHECK( program.register_uniform( "var0" ) == false );
		BOOST_CHECK( program.get_num_uniforms() == 0 );

		BOOST_REQUIRE( program.add_shader( VERTEX_SOURCE, sg::Program::VERTEX_SHADER ) == true );
		BOOST_REQUIRE( program.add_shader( FRAGMENT_SOURCE, sg::Program::FRAGMENT_SHADER ) == true );
		BOOST_REQUIRE( program.link() == true );

		// Register uniforms.
		BOOST_CHECK( program.register_uniform( "var0" ) == true );
		BOOST_CHECK( program.register_uniform( "var1" ) == true );

		BOOST_CHECK( program.is_uniform_registered( "var0" ) == true );
		BOOST_CHECK( program.is_uniform_registered( "var1" ) == true );
		BOOST_CHECK( program.get_num_uniforms() == 2 );

		// Check uniform locations.
		BOOST_CHECK( program.get_uniform_location( "var0" ) != -1 );
		BOOST_CHECK( program.get_uniform_location( "var1" ) != -1 );

		// Add another shader to check uniforms get reset.
		BOOST_CHECK( program.add_shader( VERTEX_SOURCE, sg::Program::VERTEX_SHADER ) == true );
		BOOST_CHECK( program.get_num_uniforms() == 0 );
	}
}
