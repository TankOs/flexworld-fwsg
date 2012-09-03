#pragma once

#include <FWSG/Transform.hpp>
#include <FWSG/Matrix.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace sg {

/** Camera.
 */
class Camera {
	public:
		/** Ctor.
		 * @param viewport Viewport.
		 */
		Camera( const sf::FloatRect& viewport );

		/** Setup parallel projection.
		 * @param left Left plane.
		 * @param right Right plane.
		 * @param bottom Bottom plane.
		 * @param top Top plane.
		 * @param near Near plane.
		 * @param far Far plane.
		 */
		void setup_parallel_projection( float left, float right, float bottom, float top, float near, float far );

		/** Setup perspective projection.
		 * @param fov Field of view.
		 * @param aspect Aspect ratio (width/height).
		 * @param near Near clipping plane.
		 * @param far Far clipping plane.
		 */
		void setup_perspective_projection( float fov, float aspect, float near, float far );

		/** Get transform.
		 * @return Transform.
		 */
		const Transform& get_transform() const;

		/** Set transform.
		 * @param transform Transform.
		 */
		void set_transform( const Transform& transform );

		/** Get viewport.
		 * @return Viewport.
		 */
		const sf::FloatRect& get_viewport() const;

		/** Set viewport.
		 * @param viewport Viewport.
		 */
		void set_viewport( const sf::FloatRect& viewport );

		/** Get projection matrix.
		 * @return Projection matrix.
		 */
		const FloatMatrix& get_projection_matrix() const;

		/** Get combined matrix.
		 * @return Combined matrix (projection * transformation matrix).
		 */
		const FloatMatrix& get_combined_matrix() const;

		/** Translate camera.
		 * @param translation Translation.
		 */
		void translate( const sf::Vector3f& translation );

		/** Rotate camera.
		 * @param rotation Rotation.
		 */
		void rotate( const sf::Vector3f& rotation );

	private:
		Transform m_transform;
		FloatMatrix m_projection_matrix;
		mutable FloatMatrix m_combined_matrix;
		sf::FloatRect m_viewport;
		mutable bool m_update_combined_matrix;
};

}
