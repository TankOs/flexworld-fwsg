#include <FWSG/DepthTestState.hpp>

namespace sg {

const State::Type DepthTestState::TYPE_ID = State::DEPTH_TEST;

DepthTestState::DepthTestState( bool enable ) :
	BoolState( TYPE_ID, enable )
{
}

}
