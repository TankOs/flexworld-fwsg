#pragma once

#include <FWU/Matrix.hpp>
#include <SFML/System/Vector3.hpp>

namespace sg {

/** Transform.
 * Contains properties for translation, rotation, scale and origin.
 */
class Transform {
	public:
		/** Ctor.
		 * @param translation Translation.
		 * @param rotation Rotation.
		 * @param scale Scale.
		 * @param origin Origin.
		 */
		Transform(
			const sf::Vector3f& translation = sf::Vector3f( 0, 0, 0 ),
			const sf::Vector3f& rotation = sf::Vector3f( 0, 0, 0 ),
			const sf::Vector3f& scale = sf::Vector3f( 1, 1, 1 ),
			const sf::Vector3f& origin = sf::Vector3f( 0, 0, 0 )
		);

		/** Get translation.
		 * @return Translation.
		 */
		const sf::Vector3f& get_translation() const;

		/** Set translation.
		 * @param translation Translation.
		 */
		void set_translation( const sf::Vector3f& translation );

		/** Get rotation.
		 * @return Rotation.
		 */
		const sf::Vector3f& get_rotation() const;

		/** Set rotation.
		 * @param rotation Rotation.
		 */
		void set_rotation( const sf::Vector3f& rotation );

		/** Get scale.
		 * @return Scale.
		 */
		const sf::Vector3f& get_scale() const;

		/** Set scale.
		 * @param scale Scale.
		 */
		void set_scale( const sf::Vector3f& scale );

		/** Get origin.
		 * @return Origin.
		 */
		const sf::Vector3f& get_origin() const;

		/** Set origin.
		 * @param origin Origin.
		 */
		void set_origin( const sf::Vector3f& origin );

		/** Get transformation matrix.
		 * @return Transformation matrix.
		 */
		const util::FloatMatrix& get_matrix() const;

	private:
		mutable util::FloatMatrix m_matrix;
		sf::Vector3f m_translation;
		sf::Vector3f m_rotation;
		sf::Vector3f m_scale;
		sf::Vector3f m_origin;
		mutable bool m_update_matrix;
};

/** Check for equality.
 * @param first First transform object.
 * @param second Second transform object.
 * @return true if equal.
 */
bool operator==( const Transform& first, const Transform& second );

/** Check for unequality.
 * @param first First transform object.
 * @param second Second transform object.
 * @return true if not equal.
 */
bool operator!=( const Transform& first, const Transform& second );

}
