#include <FWSG/TriangleGeometry.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestTriangleGeometry ) {
	// Initial state.
	{
		sg::TriangleGeometry tri_geo;

		BOOST_CHECK( tri_geo.get_type() == sg::Geometry::TRIANGLES );
		BOOST_CHECK( tri_geo.get_num_vertices() == 0 );
		BOOST_CHECK( tri_geo.get_num_indices() == 0 );
	}

	// Add triangles without reusing.
	{
		sg::TriangleGeometry tri_geo;

		tri_geo.add_triangle(
			sg::Vertex( sf::Vector3f( 100, 101, 102 ), sf::Vector3f( 110, 111, 112 ), sf::Vector2f( 120, 121 ), sf::Color( 130, 131, 132 ) ),
			sg::Vertex( sf::Vector3f( 200, 201, 202 ), sf::Vector3f( 210, 211, 212 ), sf::Vector2f( 220, 221 ), sf::Color( 230, 231, 232 ) ),
			sg::Vertex( sf::Vector3f( 300, 301, 302 ), sf::Vector3f( 310, 311, 312 ), sf::Vector2f( 320, 321 ), sf::Color( 30, 31, 32 ) ),
			false
		);

		tri_geo.add_triangle(
			sg::Vertex( sf::Vector3f( 400, 401, 402 ), sf::Vector3f( 410, 411, 412 ), sf::Vector2f( 420, 421 ), sf::Color( 11, 22, 33 ) ),
			sg::Vertex( sf::Vector3f( 500, 501, 502 ), sf::Vector3f( 510, 511, 512 ), sf::Vector2f( 520, 521 ), sf::Color( 44, 55, 66 ) ),
			sg::Vertex( sf::Vector3f( 600, 601, 602 ), sf::Vector3f( 610, 611, 612 ), sf::Vector2f( 620, 621 ), sf::Color( 77, 88, 99 ) ),
			false
		);

		BOOST_CHECK( tri_geo.get_num_triangles() == 2 );
		BOOST_CHECK( tri_geo.get_num_vertices() == 6 );
		BOOST_CHECK( tri_geo.get_num_indices() == 6 );

		BOOST_CHECK( tri_geo.get_vertex( 0 ) == sg::Vertex( sf::Vector3f( 100, 101, 102 ), sf::Vector3f( 110, 111, 112 ), sf::Vector2f( 120, 121 ), sf::Color( 130, 131, 132 ) ) );
		BOOST_CHECK( tri_geo.get_vertex( 1 ) == sg::Vertex( sf::Vector3f( 200, 201, 202 ), sf::Vector3f( 210, 211, 212 ), sf::Vector2f( 220, 221 ), sf::Color( 230, 231, 232 ) ) );
		BOOST_CHECK( tri_geo.get_vertex( 2 ) == sg::Vertex( sf::Vector3f( 300, 301, 302 ), sf::Vector3f( 310, 311, 312 ), sf::Vector2f( 320, 321 ), sf::Color( 30, 31, 32 ) ) );
		BOOST_CHECK( tri_geo.get_vertex( 3 ) == sg::Vertex( sf::Vector3f( 400, 401, 402 ), sf::Vector3f( 410, 411, 412 ), sf::Vector2f( 420, 421 ), sf::Color( 11, 22, 33 ) ) );
		BOOST_CHECK( tri_geo.get_vertex( 4 ) == sg::Vertex( sf::Vector3f( 500, 501, 502 ), sf::Vector3f( 510, 511, 512 ), sf::Vector2f( 520, 521 ), sf::Color( 44, 55, 66 ) ) );
		BOOST_CHECK( tri_geo.get_vertex( 5 ) == sg::Vertex( sf::Vector3f( 600, 601, 602 ), sf::Vector3f( 610, 611, 612 ), sf::Vector2f( 620, 621 ), sf::Color( 77, 88, 99 ) ) );

		BOOST_CHECK( tri_geo.get_index( 0 ) == 0 );
		BOOST_CHECK( tri_geo.get_index( 1 ) == 1 );
		BOOST_CHECK( tri_geo.get_index( 2 ) == 2 );
		BOOST_CHECK( tri_geo.get_index( 3 ) == 3 );
		BOOST_CHECK( tri_geo.get_index( 4 ) == 4 );
		BOOST_CHECK( tri_geo.get_index( 5 ) == 5 );
	}

	// Add triangles with reusing vertices.
	{
		sg::TriangleGeometry tri_geo;

		std::vector<sg::Vertex> vertices;
		vertices.push_back( sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ), sf::Color::Red ) ); // Not unique!
		vertices.push_back( sg::Vertex( sf::Vector3f( 0, 0, 1 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ), sf::Color::Black ) );
		vertices.push_back( sg::Vertex( sf::Vector3f( 1, 0, 1 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ), sf::Color::Yellow ) ); // Not unique!
		vertices.push_back( sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ), sf::Color::Red ) ); // Not unique!
		vertices.push_back( sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ), sf::Color::Black ) );
		vertices.push_back( sg::Vertex( sf::Vector3f( 1, 0, 1 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ), sf::Color::Yellow ) ); // Not unique!

		for( std::size_t idx = 0; idx < vertices.size(); idx += 3 ) {
			tri_geo.add_triangle(
				vertices[idx + 0],
				vertices[idx + 1],
				vertices[idx + 2],
				true
			);
		}

		BOOST_CHECK( tri_geo.get_num_vertices() == 4 );
		BOOST_CHECK( tri_geo.get_num_triangles() == 2 );
		BOOST_CHECK( tri_geo.get_num_indices() == 6 );

		BOOST_CHECK( tri_geo.get_vertex( 0 ) == vertices[0] );
		BOOST_CHECK( tri_geo.get_vertex( 1 ) == vertices[1] );
		BOOST_CHECK( tri_geo.get_vertex( 2 ) == vertices[2] );
		BOOST_CHECK( tri_geo.get_vertex( 3 ) == vertices[4] );

		BOOST_CHECK( tri_geo.get_index( 0 ) == 0 );
		BOOST_CHECK( tri_geo.get_index( 1 ) == 1 );
		BOOST_CHECK( tri_geo.get_index( 2 ) == 2 );
		BOOST_CHECK( tri_geo.get_index( 3 ) == 0 );
		BOOST_CHECK( tri_geo.get_index( 4 ) == 3 );
		BOOST_CHECK( tri_geo.get_index( 5 ) == 2 );
	}
}
