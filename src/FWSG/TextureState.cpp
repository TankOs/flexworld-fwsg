#include <FWSG/TextureState.hpp>

#include <cassert>

namespace sg {

const State::Type TextureState::TYPE_ID = State::TEXTURE;

TextureState::TextureState( TexturePtrConst texture, int min_filter, int mag_filter ) :
	State( State::TEXTURE ),
	m_texture( texture ),
	m_min_filter( min_filter ),
	m_mag_filter( mag_filter )
{
	assert( texture != false );
}

TextureState::TexturePtrConst TextureState::get_texture() const {
	return m_texture;
}

int TextureState::get_min_filter() const {
	return m_min_filter;
}

int TextureState::get_mag_filter() const {
	return m_mag_filter;
}

}
