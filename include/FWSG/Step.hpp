#pragma once

#include <FWSG/BufferObject.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <memory>

namespace sg {

/** Render step.
 * A render step is a concrete step executed during the rendering process. It
 * usually renders a single object with an attached shader, texture and buffer
 * object.
 * The step also includes the transformations that shall be applied.
 *
 * Make sure to notify the renderer as soon as you update a step's properties.
 */
class Step {
	public:
		typedef std::shared_ptr<const sf::Texture> TexturePtrConst; ///< Shared pointer to const SFML texture.

		/** Ctor.
		 * @param bo Buffer object.
		 */
		Step( BufferObject::PtrConst bo );

		/** Ctor.
		 * @param bo Buffer object.
		 * @param texture Texture.
		 */
		Step( BufferObject::PtrConst bo, TexturePtrConst texture );

		/** Get buffer object.
		 * @return Buffer object.
		 */
		BufferObject::PtrConst get_buffer_object() const;

		/** Get texture.
		 * @return Texture or nullptr if not set.
		 */
		TexturePtrConst get_texture() const;

		/** Set translation vector.
		 * @param translation Translation.
		 */
		void set_translation( const sf::Vector3f& translation );

		/** Get translation.
		 * @return Translation.
		 */
		const sf::Vector3f& get_translation() const;

		/** Set rotation.
		 * @param rotation Rotation (in degrees).
		 */
		 void set_rotation( const sf::Vector3f& rotation );

		 /** Get rotation.
			* @return Rotation (degrees).
			*/
		 const sf::Vector3f& get_rotation() const;

		 /** Set scale.
			* @param scale Scale.
			*/
		 void set_scale( const sf::Vector3f& scale );

		 /** Get scale.
			* @return Scale.
			*/
		 const sf::Vector3f& get_scale() const;

	private:
		BufferObject::PtrConst m_bo;
		TexturePtrConst m_texture;

		sf::Vector3f m_translation;
		sf::Vector3f m_rotation;
		sf::Vector3f m_scale;
};

}
