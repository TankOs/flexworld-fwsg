#include <FWSG/BoolState.hpp>

namespace sg {

BoolState::BoolState( Type type, bool value ) :
	State( type ),
	m_value( value )
{
}

BoolState::~BoolState() {
}

bool BoolState::is_set() const {
	return m_value;
}

}
