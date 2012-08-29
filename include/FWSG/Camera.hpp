#pragma once

#include <FWSG/Transform.hpp>

namespace sg {

/** Camera.
 */
class Camera {
	public:
		/** Projection mode.
		 */
		enum ProjectionMode {
			PERSPECTIVE = 0, ///< Perspective projection.
			PARALLEL, ///< Parallel projection.
			NUM_PROJECTION_MODES ///< Total number of projection modes.
		};

		/** Ctor.
		 */
		Camera();

		/** Get transform.
		 * @return Transform.
		 */
		const Transform& get_transform() const;

		/** Get field of view.
		 * @return Field of view.
		 */
		float get_field_of_view() const;

		/** Get near clipping plane.
		 * @return Near clipping plane.
		 */
		float get_near_clipping_plane() const;

		/** Get far clipping plane.
		 * @return Far clipping plane.
		 */
		float get_far_clipping_plane() const;

		/** Get projection mode.
		 * @return Projection mode.
		 */
		ProjectionMode get_projection_mode() const;

		/** Set transform.
		 * @param transform Transform.
		 */
		void set_transform( const Transform& transform );

		/** Set field of view.
		 * @param field_of_view Field of view (in degrees).
		 */
		void set_field_of_view( float field_of_view );

		/** Set near clipping plane.
		 * @param near_clipping_plane Near clipping plane.
		 */
		void set_near_clipping_plane( float near_clipping_plane );

		/** Set far clipping plane.
		 * @param far_clipping_plane Far clipping plane.
		 */
		void set_far_clipping_plane( float far_clipping_plane );

		/** Set projection mode.
		 * @param mode Projection mode.
		 */
		void set_projection_mode( ProjectionMode mode );

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
		float m_field_of_view;
		float m_near_clipping_plane;
		float m_far_clipping_plane;
		ProjectionMode m_projection_mode;
};

}
