#include <FWSG/ProgramCommandState.hpp>
#include <FWSG/ProgramCommand.hpp>

namespace sg {

const ProgramCommandState::Type ProgramCommandState::TYPE_ID = State::PROGRAM_COMMAND;

ProgramCommandState::ProgramCommandState( ProgramCommandPtrConst program_command ) :
	State( TYPE_ID ),
	m_program_command( program_command )
{
}

ProgramCommandState::ProgramCommandPtrConst ProgramCommandState::get_program_command() const {
	return m_program_command;
}

}
