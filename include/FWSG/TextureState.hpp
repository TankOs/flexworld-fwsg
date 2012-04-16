#include <FWSG/State.hpp>

#include <SFML/OpenGL.hpp>
#include <memory>

namespace sf {
class Texture;
}

namespace sg {

/** Texture state.
 */
class TextureState : public State {
	public:
		typedef std::shared_ptr<const sf::Texture> TexturePtrConst; ///< Shared pointer to const texture.

		static const Type TYPE_ID; ///< Texture state type ID.

		/** Ctor.
		 * Undefined behaviour if texture is null.
		 * @param texture Texture.
		 * @param min_filter Minification texture filter.
		 * @param mag_filter Magnification texture filter.
		 */
		TextureState( TexturePtrConst texture, int min_filter = GL_LINEAR, int mag_filter = GL_LINEAR );

		/** Get texture.
		 * @return Texture.
		 */
		TexturePtrConst get_texture() const;

		/** Get minification filter.
		 * @return Minification filter.
		 */
		int get_min_filter() const;

		/** Get magnification filter.
		 * @return Magnification filter.
		 */
		int get_mag_filter() const;

	private:
		TexturePtrConst m_texture;
		int m_min_filter;
		int m_mag_filter;
};

}
