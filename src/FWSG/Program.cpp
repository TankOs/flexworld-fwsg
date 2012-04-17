#include <GL/glew.h>

#include <FWSG/Program.hpp>

#include <cassert>
#include <iostream>

namespace sg {

Program::Program() :
	m_program( 0 ),
	m_is_linked( false )
{
}

Program::~Program() {
	// Delete all shaders.
	for( std::size_t shader_idx = 0; shader_idx < m_shaders.size(); ++shader_idx ) {
		glDeleteShader( m_shaders[shader_idx] );
	}

	// Delete program.
	delete_program();
}

bool Program::is_linked() const {
	return m_is_linked;
}

std::size_t Program::get_num_uniforms() const {
	return m_uniforms.size();
}

std::size_t Program::get_num_shaders() const {
	return m_shaders.size();
}

bool Program::add_shader( const std::string& source, ShaderType type ) {
	delete_program();

	// Create shader.
	GLuint shader = glCreateShader( type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER );

	if( shader == 0 ) {
		return false;
	}

	// Compile.
	const GLint length = static_cast<GLint>( source.size() );
	const char* sources = source.c_str();

	glShaderSourceARB( shader, 1, &sources, &length );
	glCompileShaderARB( shader );

	// Check if compilation succeeded.
	{
		GLint val = 0;

		glGetShaderiv( shader, GL_COMPILE_STATUS, &val );

		if( val != GL_TRUE ) {
			glDeleteShader( shader );
			return false;
		}
	}

	// Compilation succeeded.
	m_shaders.push_back( shader );

	return true;
}

bool Program::link() {
	// Delete previous program.
	delete_program();

	// Reset link state.
	m_is_linked = false;

	// Check if shaders present.
	if( m_shaders.size() == 0 ) {
		return false;
	}

	// Create program.
	m_program = glCreateProgram();

	if( m_program == 0 ) {
		return false;
	}

	// Attach shaders.
	for( std::size_t shader_idx = 0; shader_idx < m_shaders.size(); ++shader_idx ) {
		glAttachShader( m_program, m_shaders[shader_idx] );

		// Check error.
		GLint error = glGetError();

		if( error != 0 ) {
			delete_program();
			return false;
		}
	}

	// Link program.
	glLinkProgram( m_program );

	// Check success.
	{
		GLint result;

		glGetProgramiv( m_program, GL_LINK_STATUS, &result );

		if( result != GL_TRUE || glGetError() != 0 ) {
			// No success, delete program again.
			delete_program();
			return false;
		}
	}

	// Success.
	m_is_linked = true;

	return true;
}

void Program::delete_program() {
	if( m_program ) {
		glDeleteProgram( m_program );
		m_program = 0;
	}

	m_is_linked = false;

	// Remove uniform locations.
	m_uniforms.clear();
}

bool Program::register_uniform( const std::string& name ) {
	if( !m_is_linked ) {
		return false;
	}

	// Get location.
	GLint location = glGetUniformLocation( m_program, name.c_str() );

	if( location < 0 ) {
		return false;
	}

	// Success, remember location.
	m_uniforms[name] = location;

	return true;
}

bool Program::is_uniform_registered( const std::string& name ) const {
	return m_uniforms.find( name ) != m_uniforms.end();
}

void Program::use() const {
	assert( m_is_linked );

	if( m_program && m_is_linked ) {
		glUseProgram( m_program );

		if( glGetError() != 0 ) {
#if !defined( NDEBUG )
			std::cout << "WARNING: Can't use shader program." << std::endl;
#endif
		}
	}
}

GLint Program::get_uniform_location( const std::string& name ) const {
	assert( m_is_linked );
	if( !m_is_linked ) {
		return -1;
	}

	UniformMap::const_iterator uni_iter = m_uniforms.find( name );

	assert( uni_iter != m_uniforms.end() );
	if( uni_iter == m_uniforms.end() ) {
		return -1;
	}

	return uni_iter->second;
}

}
