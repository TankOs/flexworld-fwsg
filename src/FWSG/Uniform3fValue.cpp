#include <GL/glew.h>

#include <FWSG/Uniform3fValue.hpp>

namespace sg {

Uniform3fValue::Uniform3fValue( GLint location ) :
	UniformValue( location ),
	m_x( 0 ),
	m_y( 0 ),
	m_z( 0 )
{
}

void Uniform3fValue::set( float x, float y, float z ) {
	m_x = x;
	m_y = y;
	m_z = z;
}

float Uniform3fValue::get_x() const {
	return m_x;
}

float Uniform3fValue::get_y() const {
	return m_y;
}

float Uniform3fValue::get_z() const {
	return m_z;
}

void Uniform3fValue::apply() {
	glUniform3f( get_location(), m_x, m_y, m_z );
}

}
