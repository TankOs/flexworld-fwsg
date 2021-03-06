#include <FWSG/TextureState.hpp>

#include <cassert>

namespace sg {

const State::Type TextureState::TYPE_ID = State::TEXTURE;

TextureState::TextureState( TexturePtrConst texture ) :
	State( State::TEXTURE ),
	m_texture( texture )
{
	assert( texture != false );
}

TextureState::TexturePtrConst TextureState::get_texture() const {
	return m_texture;
}

}
