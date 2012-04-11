#include <FWSG/Vertex.hpp>

namespace sg {

Vertex::Vertex(
	const sf::Vector3f& vector_,
	const sf::Vector3f& normal_,
	const sf::Vector2f& uv_,
	const sf::Color& color_
) :
	vector( vector_ ),
	normal( normal_ ),
	uv( uv_ ),
	color( color_ )
{
}

Vertex::Vertex(
	const sf::Vector3f& vector_,
	const sf::Vector2f& uv_
) :
	vector( vector_ ),
	normal( 0, 0, 0 ),
	uv( uv_ ),
	color( sf::Color::White )
{
}

bool operator==( const Vertex& first, const Vertex& second ) {
	return
		first.vector == second.vector &&
		first.normal == second.normal &&
		first.uv == second.uv &&
		first.color == second.color
	;
}

bool operator!=( const Vertex& first, const Vertex& second ) {
	return
		first.vector != second.vector ||
		first.normal != second.normal ||
		first.uv != second.uv ||
		first.color != second.color
	;
}


}
