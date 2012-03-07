#include <FWSG/Transform.hpp>

#include <cassert>

namespace sg {

bool operator==( const Transform& first, const Transform& second ) {
	return
		(first.get_translation() == second.get_translation()) &&
		(first.get_rotation() == second.get_rotation()) &&
		(first.get_scale() == second.get_scale())
	;
}

bool operator!=( const Transform& first, const Transform& second ) {
	return
		(first.get_translation() != second.get_translation()) ||
		(first.get_rotation() != second.get_rotation()) ||
		(first.get_scale() != second.get_scale())
	;
}

Transform operator+( const Transform& first, const Transform& second ) {
	return Transform(
		first.get_translation() + second.get_translation(),
		first.get_rotation() + second.get_rotation(),
		sf::Vector3f(
			first.get_scale().x * second.get_scale().x,
			first.get_scale().y * second.get_scale().y,
			first.get_scale().z * second.get_scale().z
		)
	);
}

Transform::Transform( const sf::Vector3f& translation, const sf::Vector3f& rotation, const sf::Vector3f& scale ) :
	m_translation( translation ),
	m_rotation( rotation ),
	m_scale( scale )
{
	assert( scale.x > 0 );
	assert( scale.y > 0 );
	assert( scale.z > 0 );
}

const sf::Vector3f& Transform::get_translation() const {
	return m_translation;
}

void Transform::set_translation( const sf::Vector3f& translation ) {
	m_translation = translation;
}

const sf::Vector3f& Transform::get_rotation() const {
	return m_rotation;
}

void Transform::set_rotation( const sf::Vector3f& rotation ) {
	m_rotation = rotation;
}

const sf::Vector3f& Transform::get_scale() const {
	return m_scale;
}

void Transform::set_scale( const sf::Vector3f& scale ) {
	assert( scale.x > 0 );
	assert( scale.y > 0 );
	assert( scale.z > 0 );

	m_scale = scale;
}

}
