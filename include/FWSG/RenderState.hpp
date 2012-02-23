#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <memory>

namespace sg {

/** Render state.
 */
struct RenderState {
	/** Ctor.
	 */
	RenderState();

	std::shared_ptr<const sf::Texture> texture;
	bool wireframe;
	bool depth_test;
	bool cull;
};

}
