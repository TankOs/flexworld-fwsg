#include <FWSG/Step.hpp>

namespace sg {

Step::Step( BufferObject::PtrConst bo ) :
	m_bo( bo ),
	m_translation( 0, 0, 0 ),
	m_rotation( 0, 0, 0 ),
	m_scale( 1, 1, 1 )
{
}

BufferObject::PtrConst Step::get_buffer_object() const {
	return m_bo;
}

void Step::set_translation( const sf::Vector3f& translation ) {
	m_translation = translation;
}

const sf::Vector3f& Step::get_translation() const {
	return m_translation;
}

void Step::set_rotation( const sf::Vector3f& rotation ) {
	m_rotation = rotation;
}

const sf::Vector3f& Step::get_rotation() const {
	return m_rotation;
}

void Step::set_scale( const sf::Vector3f& scale ) {
	m_scale = scale;
}

const sf::Vector3f& Step::get_scale() const {
	return m_scale;
}

}
