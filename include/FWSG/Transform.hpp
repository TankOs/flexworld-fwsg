#pragma once

#include <SFML/System/Vector3.hpp>

namespace sg {

/** Transform.
 * Contains properties for translation, rotation and scale.
 */
class Transform {
	public:
		/** Ctor.
		 * @param translation Translation.
		 * @param rotation Rotation.
		 * @param scale Scale.
		 */
		Transform(
			const sf::Vector3f& translation = sf::Vector3f( 0, 0, 0 ),
			const sf::Vector3f& rotation = sf::Vector3f( 0, 0, 0 ),
			const sf::Vector3f& scale = sf::Vector3f( 1, 1, 1 )
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

	private:
		sf::Vector3f m_translation;
		sf::Vector3f m_rotation;
		sf::Vector3f m_scale;
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

/** Add transform.
 * Scales are multiplied!
 * @param first First transform object.
 * @param second Second transform object.
 * @return first + second
 */
Transform operator+( const Transform& first, const Transform& second );

}