#include <FWSG/State.hpp>

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

		/** Ctor.
		 * Undefined behaviour if texture is null.
		 * @param texture Texture.
		 */
		TextureState( TexturePtrConst texture );

		/** Get texture.
		 * @return Texture.
		 */
		TexturePtrConst get_texture() const;

	private:
		TexturePtrConst m_texture;
};

}
