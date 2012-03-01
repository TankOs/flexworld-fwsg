#include <FWSG/Geometry.hpp>

#include <cassert>

namespace sg {

Geometry::Geometry( Type type ) :
	m_type( type )
{
}

Geometry::~Geometry() {
}

std::size_t Geometry::get_num_vertices() const {
	return m_vertices.size();
}

std::size_t Geometry::get_num_indices() const {
	return m_indices.size();
}

Geometry::Type Geometry::get_type() const {
	return m_type;
}

void Geometry::add_vertex( const Vertex& vertex ) {
	m_vertices.push_back( vertex );
}

void Geometry::add_index( uint32_t index ) {
	assert( index < m_vertices.size() );

	m_indices.push_back( index );
}

}
