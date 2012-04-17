#include <FWSG/ProgramCommand.hpp>
#include <FWSG/Program.hpp>
#include <FWSG/UniformValue.hpp>
#include <FWSG/Uniform1fValue.hpp>
#include <FWSG/Uniform2fValue.hpp>
#include <FWSG/Uniform3fValue.hpp>
#include <FWSG/Uniform4fValue.hpp>

#include <cassert>

namespace sg {

ProgramCommand::ProgramCommand( std::shared_ptr<const Program> program ) :
	m_program( program )
{
}

ProgramCommand::~ProgramCommand() {
	// Delete values.
	for( std::size_t idx = 0; idx < m_values.size(); ++idx ) {
		delete m_values[idx];
	}
}

std::shared_ptr<const Program> ProgramCommand::get_program() const {
	return m_program;
}

std::size_t ProgramCommand::get_num_arguments() const {
	return m_values.size();
}

void ProgramCommand::set_argument( const std::string& name, float value ) {
	// Fetch location.
	GLint location = get_program()->get_uniform_location( name );
	
	assert( location != -1 );
	if( location == -1 ) {
		return;
	}

	Uniform1fValue* arg = find_or_create_argument<Uniform1fValue>( name, location );
	assert( arg != nullptr );

	arg->set( value );
}

void ProgramCommand::set_argument( const std::string& name, float x, float y ) {
	// Fetch location.
	GLint location = get_program()->get_uniform_location( name );
	
	assert( location != -1 );
	if( location == -1 ) {
		return;
	}

	Uniform2fValue* arg = find_or_create_argument<Uniform2fValue>( name, location );
	assert( arg != nullptr );

	arg->set( x, y );
}

void ProgramCommand::set_argument( const std::string& name, float x, float y, float z ) {
	// Fetch location.
	GLint location = get_program()->get_uniform_location( name );
	
	assert( location != -1 );
	if( location == -1 ) {
		return;
	}

	Uniform3fValue* arg = find_or_create_argument<Uniform3fValue>( name, location );
	assert( arg != nullptr );

	arg->set( x, y, z );
}

void ProgramCommand::set_argument( const std::string& name, float x, float y, float z, float w ) {
	// Fetch location.
	GLint location = get_program()->get_uniform_location( name );
	
	assert( location != -1 );
	if( location == -1 ) {
		return;
	}

	Uniform4fValue* arg = find_or_create_argument<Uniform4fValue>( name, location );
	assert( arg != nullptr );

	arg->set( x, y, z, w );
}

const UniformValue* ProgramCommand::get_argument( std::size_t index ) const {
	assert( index < m_values.size() );

	return m_values[index];
}

void ProgramCommand::apply_uniform_values() const {
	std::size_t num = m_values.size();

	for( std::size_t idx = 0; idx < num; ++idx ) {
		m_values[idx]->apply();
	}
}

}
