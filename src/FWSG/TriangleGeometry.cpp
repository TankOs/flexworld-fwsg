#include <FWSG/TriangleGeometry.hpp>

#include <cassert>

namespace sg {

TriangleGeometry::TriangleGeometry() :
	Geometry( TRIANGLES )
{
}

void TriangleGeometry::add_triangle( const Vertex& a, const Vertex& b, const Vertex& c, bool reuse ) {
	std::size_t vertex_indices[3] = {get_num_vertices(), get_num_vertices(), get_num_vertices()};
	std::size_t num_vertices = get_num_vertices();

	// Reuse, look for each vertex.
	if( reuse ) {
		for( std::size_t vertex_idx = 0; vertex_idx < num_vertices; ++vertex_idx ) {
			const Vertex& vertex = get_vertex( static_cast<uint32_t>( vertex_idx ) );

			if( vertex_indices[0] >= num_vertices && a == vertex ) {
				vertex_indices[0] = vertex_idx;
			}

			if( vertex_indices[1] >= num_vertices && b == vertex ) {
				vertex_indices[1] = vertex_idx;
			}

			if( vertex_indices[2] >= num_vertices && c == vertex ) {
				vertex_indices[2] = vertex_idx;
			}
		}
	}

	// Check which indices are out-of-scope, telling us that those are not
	// existing or the user didn't want to reuse vertices.
	if( vertex_indices[0] >= num_vertices ) {
		add_vertex( a );
		vertex_indices[0] = get_num_vertices() - 1;
	}

	if( vertex_indices[1] >= num_vertices ) {
		add_vertex( b );
		vertex_indices[1] = get_num_vertices() - 1;
	}

	if( vertex_indices[2] >= num_vertices ) {
		add_vertex( c );
		vertex_indices[2] = get_num_vertices() - 1;
	}

	// Define the triangle.
	add_index( static_cast<uint32_t>( vertex_indices[0] ) );
	add_index( static_cast<uint32_t>( vertex_indices[1] ) );
	add_index( static_cast<uint32_t>( vertex_indices[2] ) );
}

std::size_t TriangleGeometry::get_num_triangles() const {
	assert( get_num_indices() % 3 == 0 );
	return get_num_indices() / 3;
}

}
