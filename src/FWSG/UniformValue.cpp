#include <FWSG/UniformValue.hpp>

namespace sg {

UniformValue::UniformValue( GLint location ) :
	m_location( location )
{
}

UniformValue::~UniformValue() {
}

GLint UniformValue::get_location() const {
	return m_location;
}

}
