#include <GL/glew.h>

#include <FWSG/Uniform1fValue.hpp>

namespace sg {

Uniform1fValue::Uniform1fValue( GLint location ) :
	UniformValue( location ),
	m_value( 0 )
{
}

void Uniform1fValue::set( float value ) {
	m_value = value;
}

float Uniform1fValue::get() const {
	return m_value;
}

void Uniform1fValue::apply() {
	glUniform1f( get_location(), m_value );
}

}
