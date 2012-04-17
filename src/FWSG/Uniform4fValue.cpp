#include <GL/glew.h>

#include <FWSG/Uniform4fValue.hpp>

namespace sg {

Uniform4fValue::Uniform4fValue( GLint location ) :
	UniformValue( location ),
	m_x( 0 ),
	m_y( 0 ),
	m_z( 0 ),
	m_w( 0 )
{
}

void Uniform4fValue::set( float x, float y, float z, float w ) {
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = w;
}

float Uniform4fValue::get_x() const {
	return m_x;
}

float Uniform4fValue::get_y() const {
	return m_y;
}

float Uniform4fValue::get_z() const {
	return m_z;
}

float Uniform4fValue::get_w() const {
	return m_w;
}

void Uniform4fValue::apply() {
	glUniform4f( get_location(), m_x, m_y, m_z, m_w );
}

}
