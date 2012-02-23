#include <FWSG/WireframeState.hpp>

namespace sg {

const State::Type WireframeState::TYPE_ID = State::WIREFRAME;

WireframeState::WireframeState( bool enable ) :
	BoolState( TYPE_ID, enable )
{
}

}
