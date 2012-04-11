#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace sg {

/** 3-dimensional vertex with normal and tex coords.
 */
struct Vertex {
	/** Ctor.
	 * @param vector_ Vector.
	 * @param normal_ Normal.
	 * @param uv_ Texture coordinate.
	 */
	Vertex(
		const sf::Vector3f& vector_ = sf::Vector3f( 0, 0, 0 ),
		const sf::Vector3f& normal_ = sf::Vector3f( 0, 0, 0 ),
		const sf::Vector2f& uv_ = sf::Vector2f( 0, 0 ),
		const sf::Color& color_ = sf::Color::White
	);

	/** Ctor.
	 * @param vector_ Vector.
	 * @param uv_ Texture coordinate.
	 */
	Vertex(
		const sf::Vector3f& vector_,
		const sf::Vector2f& uv_
	);

	sf::Vector3f vector; ///< Vector.
	sf::Vector3f normal; ///< Normal vector.
	sf::Vector2f uv; ///< Texture coordinate.
	sf::Color color; ///< Color.
};

/** Check for equal vertices.
 * @param first First vertex.
 * @param second Second vertex.
 * @return true if equal.
 */
bool operator==( const Vertex& first, const Vertex& second );

/** Check for unequal vertices.
 * @param first First vertex.
 * @param second Second vertex.
 * @return true if unequal.
 */
bool operator!=( const Vertex& first, const Vertex& second );

}
