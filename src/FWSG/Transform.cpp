#include <FWSG/Transform.hpp>

#include <cassert>

namespace sg {

bool operator==( const Transform& first, const Transform& second ) {
	return
		(first.get_translation() == second.get_translation()) &&
		(first.get_rotation() == second.get_rotation()) &&
		(first.get_scale() == second.get_scale()) &&
		(first.get_origin() == second.get_origin())
	;
}

bool operator!=( const Transform& first, const Transform& second ) {
	return
		(first.get_translation() != second.get_translation()) ||
		(first.get_rotation() != second.get_rotation()) ||
		(first.get_scale() != second.get_scale()) ||
		(first.get_origin() != second.get_origin())
	;
}

Transform::Transform( const sf::Vector3f& translation, const sf::Vector3f& rotation, const sf::Vector3f& scale, const sf::Vector3f& origin ) :
	m_translation( translation ),
	m_rotation( rotation ),
	m_scale( scale ),
	m_origin( origin )
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

void Transform::set_origin( const sf::Vector3f& origin ) {
	m_origin = origin;
}

const sf::Vector3f& Transform::get_origin() const {
	return m_origin;
}

}
