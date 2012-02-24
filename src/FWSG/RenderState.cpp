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

bool RenderState::operator!=( const RenderState& other ) const {
	return
		texture.get() != other.texture.get() ||
		wireframe != other.wireframe ||
		depth_test != other.depth_test ||
		cull != other.cull
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

	if( cull && !other.cull ) {
		return true;
	}
	else if( !cull && other.cull ) {
		return false;
	}

	// Equal at this point.
	return false;
}

}
