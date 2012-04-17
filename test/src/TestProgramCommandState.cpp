#include "Window.hpp"

#include <FWSG/ProgramCommandState.hpp>
#include <FWSG/Program.hpp>
#include <FWSG/ProgramCommand.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestProgramCommandState ) {
	init_test_window();

	BOOST_CHECK( sg::ProgramCommandState::TYPE_ID == sg::State::PROGRAM_COMMAND );

	// Create test program.
	sg::Program::Ptr program( new sg::Program );
	BOOST_REQUIRE( program->add_shader( "void main() { gl_FragColor = vec4( 1, 1, 1, 1 ); }", sg::Program::FRAGMENT_SHADER ) );
	BOOST_REQUIRE( program->link() );

	// Create test program command.
	sg::ProgramCommand::Ptr program_command( new sg::ProgramCommand( program ) );

	// Initial state.
	{
		sg::ProgramCommandState prg_state( program_command );

		BOOST_CHECK( prg_state.get_type() == sg::ProgramCommandState::TYPE_ID );
		BOOST_CHECK( prg_state.get_program_command() == program_command );
	}
}
