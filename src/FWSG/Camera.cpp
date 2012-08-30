#include <FWSG/Camera.hpp>

namespace sg {

Camera::Camera() :
	m_field_of_view( 80.0f ),
	m_near_clipping_plane( 0.1f ),
	m_far_clipping_plane( 100.0f ),
	m_aspect_ratio( 1.0f ),
	m_projection_mode( PERSPECTIVE )
{
}

const Transform& Camera::get_transform() const {
	return m_transform;
}

float Camera::get_field_of_view() const {
	return m_field_of_view;
}

float Camera::get_near_clipping_plane() const {
	return m_near_clipping_plane;
}

float Camera::get_far_clipping_plane() const {
	return m_far_clipping_plane;
}

Camera::ProjectionMode Camera::get_projection_mode() const {
	return m_projection_mode;
}

float Camera::get_aspect_ratio() const {
	return m_aspect_ratio;
}

void Camera::set_transform( const Transform& transform ) {
	m_transform = transform;
}

void Camera::set_field_of_view( float field_of_view ) {
	m_field_of_view = field_of_view;
}

void Camera::set_near_clipping_plane( float near_clipping_plane ) {
	m_near_clipping_plane = near_clipping_plane;
}

void Camera::set_far_clipping_plane( float far_clipping_plane ) {
	m_far_clipping_plane = far_clipping_plane;
}

void Camera::set_projection_mode( ProjectionMode mode ) {
	m_projection_mode = mode;
}

void Camera::set_aspect_ratio( float aspect_ratio ) {
	m_aspect_ratio = aspect_ratio;
}

void Camera::translate( const sf::Vector3f& translation ) {
	m_transform.set_translation( m_transform.get_translation() + translation );
}

void Camera::rotate( const sf::Vector3f& rotation ) {
	m_transform.set_rotation( m_transform.get_rotation() + rotation );
}

}
