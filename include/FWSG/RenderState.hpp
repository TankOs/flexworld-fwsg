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

	/** Equality.
	 * @param other Other RenderState object.
	 * @return true if equal.
	 */
	bool operator==( const RenderState& other ) const;

	/** Unequality.
	 * @param other Other RenderState object.
	 * @return true if unequal.
	 */
	bool operator!=( const RenderState& other ) const;

	/** Less than.
	 * Order of comparison: Texture (pointer), wireframe (true/false), depth test
	 * (true/false), cull (true/false).
	 * @param other Other RenderState object.
	 * @return true if less than other object.
	 */
	bool operator<( const RenderState& other ) const;

	std::shared_ptr<const sf::Texture> texture;
	bool wireframe;
	bool depth_test;
	bool cull;
};

}
