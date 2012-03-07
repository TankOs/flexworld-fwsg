#include <FWSG/BackfaceCullingState.hpp>

namespace sg {

const State::Type BackfaceCullingState::TYPE_ID = State::BACKFACE_CULLING;

BackfaceCullingState::BackfaceCullingState( bool enable ) :
	BoolState( TYPE_ID, enable )
{
}

}
