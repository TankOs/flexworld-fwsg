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
	m_origin( origin ),
	m_update_matrix( true )
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
	m_update_matrix = true;
}

const sf::Vector3f& Transform::get_rotation() const {
	return m_rotation;
}

void Transform::set_rotation( const sf::Vector3f& rotation ) {
	m_rotation = rotation;
	m_update_matrix = true;
}

const sf::Vector3f& Transform::get_scale() const {
	return m_scale;
}

void Transform::set_scale( const sf::Vector3f& scale ) {
	assert( scale.x > 0 );
	assert( scale.y > 0 );
	assert( scale.z > 0 );

	m_scale = scale;
	m_update_matrix = true;
}

void Transform::set_origin( const sf::Vector3f& origin ) {
	m_origin = origin;
	m_update_matrix = true;
}

const sf::Vector3f& Transform::get_origin() const {
	return m_origin;
}

const FloatMatrix& Transform::get_matrix() const {
	if( m_update_matrix ) {
		m_matrix.reset();
		m_matrix.translate( m_translation );
		m_matrix.rotate( m_rotation );
		m_matrix.scale( m_scale );
		m_matrix.translate( sf::Vector3f( -m_origin.x, -m_origin.y, -m_origin.z ) );

		m_update_matrix = false;
	}

	return m_matrix;
}

}
