#include <FWSG/Camera.hpp>

namespace sg {

Camera::Camera( const sf::FloatRect& viewport ) :
	m_viewport( viewport ),
	m_update_combined_matrix( false )
{
}

void Camera::setup_parallel_projection( float left, float right, float bottom, float top, float near, float far ) {
	m_projection_matrix = FloatMatrix(
		2.0f / (right - left), 0.0f, 0.0f, -((right + left) / (right - left)),
		0.0f, 2.0f / (top - bottom), 0.0f, -((top + bottom) / (top - bottom)),
		0.0f, 0.0f, -2.0f / (far - near),  -((far + near)   / (far - near)),
		0.0f, 0.0f, 0.0f, 1.0f
	);

	m_update_combined_matrix = true;
}

void Camera::setup_perspective_projection( float fov, float aspect, float near, float far ) {
	float f = 1.0f / std::tan( (fov * PI / 180.0f) / 2.0f );

	m_projection_matrix = FloatMatrix(
		f / aspect, 0.0f, 0.0f, 0.0f,
		0.0f, f, 0.0f, 0.0f,
		0.0f, 0.0f, (far + near) / (near - far), (2.0f * far * near) / (near - far),
		0.0f, 0.0f, -1.0f, 0.0f
	);

	m_update_combined_matrix = true;
}

const Transform& Camera::get_transform() const {
	return m_transform;
}

void Camera::set_transform( const Transform& transform ) {
	m_transform = transform;

	m_update_combined_matrix = true;
}

const sf::FloatRect& Camera::get_viewport() const {
	return m_viewport;
}

void Camera::set_viewport( const sf::FloatRect& viewport ) {
	m_viewport = viewport;
}

const FloatMatrix& Camera::get_projection_matrix() const {
	return m_projection_matrix;
}

void Camera::translate( const sf::Vector3f& translation ) {
	m_transform.set_translation( m_transform.get_translation() + translation );

	m_update_combined_matrix = true;
}

void Camera::rotate( const sf::Vector3f& rotation ) {
	m_transform.set_rotation( m_transform.get_rotation() + rotation );

	m_update_combined_matrix = true;
}

const FloatMatrix& Camera::get_combined_matrix() const {
	if( m_update_combined_matrix ) {
		m_combined_matrix = m_projection_matrix;

		// Calculate negation of current transform matrix, because the scene is
		// about to be shifted in the opposite direction.
		Transform negated_transform(
			sf::Vector3f(
				-m_transform.get_translation().x,
				-m_transform.get_translation().y,
				-m_transform.get_translation().z
			),
			sf::Vector3f(
				-m_transform.get_rotation().x,
				-m_transform.get_rotation().y,
				-m_transform.get_rotation().z
			),
			m_transform.get_scale(),
			sf::Vector3f(
				-m_transform.get_origin().x,
				-m_transform.get_origin().y,
				-m_transform.get_origin().z
			)
		);

		m_combined_matrix.multiply( negated_transform.get_matrix() );

		m_update_combined_matrix = false;
	}

	return m_combined_matrix;
}

}
