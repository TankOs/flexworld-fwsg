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

		// Add another shader to check uniforms get reset.
		BOOST_CHECK( program.add_shader( VERTEX_SOURCE, sg::Program::VERTEX_SHADER ) == true );
		BOOST_CHECK( program.get_num_uniforms() == 0 );
	}

	// Set uniforms.
	{
		const std::string VERTEX_SOURCE = "uniform float float_var; uniform vec2 vec2_var; uniform vec3 vec3_var; uniform vec4 vec4_var; void main() { gl_Position = vec4( float_var, vec2_var.x, vec3_var.x, vec4_var.x ); }";
		const std::string FRAGMENT_SOURCE = "uniform int int_var; uniform ivec2 ivec2_var; uniform ivec3 ivec3_var; uniform ivec4 ivec4_var; void main() { gl_FragColor = vec4( int_var, ivec2_var.x, ivec3_var.x, ivec4_var.x ); }";

		sg::Program program;

		// Try to register uniform without linked program.
		BOOST_CHECK( program.register_uniform( "var0" ) == false );
		BOOST_CHECK( program.get_num_uniforms() == 0 );

		BOOST_REQUIRE( program.add_shader( VERTEX_SOURCE, sg::Program::VERTEX_SHADER ) == true );
		BOOST_REQUIRE( program.add_shader( FRAGMENT_SOURCE, sg::Program::FRAGMENT_SHADER ) == true );
		BOOST_REQUIRE( program.link() == true );

		// Register uniforms.
		BOOST_REQUIRE( program.register_uniform( "float_var" ) == true );
		BOOST_REQUIRE( program.register_uniform( "vec2_var" ) == true );
		BOOST_REQUIRE( program.register_uniform( "vec3_var" ) == true );
		BOOST_REQUIRE( program.register_uniform( "vec4_var" ) == true );
		BOOST_REQUIRE( program.register_uniform( "int_var" ) == true );
		BOOST_REQUIRE( program.register_uniform( "ivec2_var" ) == true );
		BOOST_REQUIRE( program.register_uniform( "ivec3_var" ) == true );
		BOOST_REQUIRE( program.register_uniform( "ivec4_var" ) == true );
		BOOST_REQUIRE( program.get_num_uniforms() == 8 );

		// Set values.
		BOOST_CHECK( program.set_uniform( "float_var", 123.0f ) == true );
		BOOST_CHECK( program.set_uniform( "vec2_var", 123.0f, 123.0f ) == true );
		BOOST_CHECK( program.set_uniform( "vec3_var", 123.0f, 123.0f, 123.0f ) == true );
		BOOST_CHECK( program.set_uniform( "vec4_var", 123.0f, 123.0f, 123.0f, 123.0f ) == true );

		BOOST_CHECK( program.set_uniform( "int_var", 123 ) == true );
		BOOST_CHECK( program.set_uniform( "ivec2_var", 123, 123 ) == true );
		BOOST_CHECK( program.set_uniform( "ivec3_var", 123, 123, 123 ) == true );
		BOOST_CHECK( program.set_uniform( "ivec4_var", 123, 123, 123, 123 ) == true );

		// Set values with type-mismatch.
		BOOST_CHECK( program.set_uniform( "float_var", 123 ) == false );
		BOOST_CHECK( program.set_uniform( "vec2_var", 123, 123 ) == false );
		BOOST_CHECK( program.set_uniform( "vec3_var", 123, 123, 123 ) == false );
		BOOST_CHECK( program.set_uniform( "vec4_var", 123, 123, 123, 123 ) == false );

		BOOST_CHECK( program.set_uniform( "int_var", 123.0f ) == false );
		BOOST_CHECK( program.set_uniform( "ivec2_var", 123.0f, 123.0f ) == false );
		BOOST_CHECK( program.set_uniform( "ivec3_var", 123.0f, 123.0f, 123.0f ) == false );
		BOOST_CHECK( program.set_uniform( "ivec4_var", 123.0f, 123.0f, 123.0f, 123.0f ) == false );
	}
}
