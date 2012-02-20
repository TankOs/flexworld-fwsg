#include <FWSG/Vertex.hpp>

namespace sg {

Vertex::Vertex(
	const sf::Vector3f& vector_,
	const sf::Vector3f& normal_,
	const sf::Vector2f& uv_
) :
	vector( vector_ ),
	normal( normal_ ),
	uv( uv_ )
{
}

bool operator==( const Vertex& first, const Vertex& second ) {
	return
		first.vector == second.vector &&
		first.normal == second.normal &&
		first.uv == second.uv
	;
}

bool operator!=( const Vertex& first, const Vertex& second ) {
	return
		first.vector != second.vector ||
		first.normal != second.normal ||
		first.uv != second.uv
	;
}


}
