#include <FWSG/State.hpp>

#include <cassert>

namespace sg {

State::State( Type type ) :
	m_type( type )
{
	assert( type >= SHADER && type < NUM_TYPES );
}

State::~State() {
}

State::Type State::get_type() const {
	return m_type;
}

}
