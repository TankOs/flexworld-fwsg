#include <GL/glew.h>

#include <FWSG/Uniform2fValue.hpp>

namespace sg {

Uniform2fValue::Uniform2fValue( GLint location ) :
	UniformValue( location ),
	m_x( 0 ),
	m_y( 0 )
{
}

void Uniform2fValue::set( float x, float y ) {
	m_x = x;
	m_y = y;
}

float Uniform2fValue::get_x() const {
	return m_x;
}

float Uniform2fValue::get_y() const {
	return m_y;
}

void Uniform2fValue::apply() {
	glUniform2f( get_location(), m_x, m_y );
}

}
