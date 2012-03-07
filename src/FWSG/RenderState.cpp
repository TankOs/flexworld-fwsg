#include <FWSG/RenderState.hpp>

namespace sg {

RenderState::RenderState() :
	wireframe( false ),
	depth_test( false ),
	backface_culling( true )
{
}

bool RenderState::operator==( const RenderState& other ) const {
	return
		texture.get() == other.texture.get() &&
		wireframe == other.wireframe &&
		depth_test == other.depth_test &&
		backface_culling == other.backface_culling
	;
}

bool RenderState::operator!=( const RenderState& other ) const {
	return
		texture.get() != other.texture.get() ||
		wireframe != other.wireframe ||
		depth_test != other.depth_test ||
		backface_culling != other.backface_culling
	;
}

bool RenderState::operator<( const RenderState& other ) const {
	if( texture.get() < other.texture.get() ) {
		return true;
	}
	else if( texture.get() > other.texture.get() ) {
		return false;
	}

	if( wireframe && !other.wireframe ) {
		return true;
	}
	else if( !wireframe && other.wireframe ) {
		return false;
	}

	if( depth_test && !other.depth_test ) {
		return true;
	}
	else if( !depth_test && other.depth_test ) {
		return false;
	}

	if( backface_culling && !other.backface_culling ) {
		return true;
	}
	else if( !backface_culling && other.backface_culling ) {
		return false;
	}

	// Equal at this point.
	return false;
}

}
