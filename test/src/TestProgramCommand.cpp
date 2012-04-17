#include "Window.hpp"

#include <FWSG/ProgramCommand.hpp>
#include <FWSG/Program.hpp>
#include <FWSG/Uniform1fValue.hpp>
#include <FWSG/Uniform2fValue.hpp>
#include <FWSG/Uniform3fValue.hpp>
#include <FWSG/Uniform4fValue.hpp>

#include <boost/test/unit_test.hpp>
#include <string>

BOOST_AUTO_TEST_CASE( TestProgramCommand ) {
	init_test_window();

	const std::string FRAGMENT_SOURCE = " \
		uniform float f_solo; \
		uniform vec2 f_vec2; \
		uniform vec3 f_vec3; \
		uniform vec4 f_vec4; \
		\
		void main() { \
			gl_FragColor = vec4( f_solo + f_vec2.x + f_vec3.x + f_vec4.x, 0, 0, 0 ); \
		} \
	";

	// Create a program.
	sg::Program::Ptr program( new sg::Program );
	BOOST_REQUIRE( program->add_shader( FRAGMENT_SOURCE, sg::Program::FRAGMENT_SHADER ) == true );
	BOOST_REQUIRE( program->link() );

	BOOST_REQUIRE( program->register_uniform( "f_solo" ) == true );
	BOOST_REQUIRE( program->register_uniform( "f_vec2" ) == true );
	BOOST_REQUIRE( program->register_uniform( "f_vec3" ) == true );
	BOOST_REQUIRE( program->register_uniform( "f_vec4" ) == true );

	// Initial state.
	{
		sg::ProgramCommand command( program );

		BOOST_CHECK( command.get_program() == program );
		BOOST_CHECK( command.get_num_arguments() == 0 );
	}

	// Set arguments.
	{
		sg::ProgramCommand command( program );

		// Float, solo.
		command.set_argument( "f_solo", 1.0f );
		BOOST_CHECK( command.get_num_arguments() == 1 );
		BOOST_CHECK( dynamic_cast<const sg::Uniform1fValue*>( command.get_argument( 0 ) ) != nullptr );

		{
			const sg::Uniform1fValue* arg = command.find_argument<sg::Uniform1fValue>( "f_solo" );

			BOOST_CHECK( arg );

			if( arg ) {
				BOOST_CHECK( arg->get() == 1.0f );
			}
		}

		// Float, vec2.
		command.set_argument( "f_vec2", 1.0f, 2.0f );
		BOOST_CHECK( command.get_num_arguments() == 2 );
		BOOST_CHECK( dynamic_cast<const sg::Uniform2fValue*>( command.get_argument( 1 ) ) != nullptr );

		{
			const sg::Uniform2fValue* arg = command.find_argument<sg::Uniform2fValue>( "f_vec2" );

			BOOST_CHECK( arg );

			if( arg ) {
				BOOST_CHECK( arg->get_x() == 1.0f );
				BOOST_CHECK( arg->get_y() == 2.0f );
			}
		}

		// Float, vec3.
		command.set_argument( "f_vec3", 1.0f, 2.0f, 3.0f );
		BOOST_CHECK( command.get_num_arguments() == 3 );
		BOOST_CHECK( dynamic_cast<const sg::Uniform3fValue*>( command.get_argument( 2 ) ) != nullptr );

		{
			const sg::Uniform3fValue* arg = command.find_argument<sg::Uniform3fValue>( "f_vec3" );

			BOOST_CHECK( arg );

			if( arg ) {
				BOOST_CHECK( arg->get_x() == 1.0f );
				BOOST_CHECK( arg->get_y() == 2.0f );
				BOOST_CHECK( arg->get_z() == 3.0f );
			}
		}

		// Float, vec4.
		command.set_argument( "f_vec4", 1.0f, 2.0f, 3.0f, 4.0f );
		BOOST_CHECK( command.get_num_arguments() == 4 );
		BOOST_CHECK( dynamic_cast<const sg::Uniform4fValue*>( command.get_argument( 3 ) ) != nullptr );

		{
			const sg::Uniform4fValue* arg = command.find_argument<sg::Uniform4fValue>( "f_vec4" );

			BOOST_CHECK( arg );

			if( arg ) {
				BOOST_CHECK( arg->get_x() == 1.0f );
				BOOST_CHECK( arg->get_y() == 2.0f );
				BOOST_CHECK( arg->get_z() == 3.0f );
				BOOST_CHECK( arg->get_w() == 4.0f );
			}
		}
	}
}
