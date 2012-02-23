#include <FWSG/RenderState.hpp>

namespace sg {

RenderState::RenderState() :
	wireframe( false ),
	depth_test( false ),
	cull( false )
{
}

bool RenderState::operator==( const RenderState& other ) const {
	return
		texture.get() == other.texture.get() &&
		wireframe == other.wireframe &&
		depth_test == other.depth_test &&
		cull == other.cull
	;
}

}
