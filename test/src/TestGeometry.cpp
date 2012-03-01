#include <FWSG/Geometry.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestGeometry ) {
	// Initial state.
	{
		sg::Geometry geo;

		BOOST_CHECK( geo.get_type() == sg::Geometry::TRIANGLES );
		BOOST_CHECK( geo.get_num_vertices() == 0 );
		BOOST_CHECK( geo.get_num_indices() == 0 );
	}

	// Add vertices and indices.
	{
		sg::Geometry geo;

		geo.add_vertex( sg::Vertex( sf::Vector3f( 100, 101, 102 ), sf::Vector3f( 110, 111, 121 ), sf::Vector2f( 120, 121 ) ) );
		geo.add_vertex( sg::Vertex( sf::Vector3f( 200, 201, 202 ), sf::Vector3f( 210, 211, 221 ), sf::Vector2f( 220, 221 ) ) );
		geo.add_vertex( sg::Vertex( sf::Vector3f( 300, 301, 302 ), sf::Vector3f( 310, 311, 321 ), sf::Vector2f( 320, 321 ) ) );
		BOOST_CHECK( geo.get_num_vertices() == 3 );

		geo.add_index( 0 );
		geo.add_index( 1 );
		geo.add_index( 2 );
		BOOST_CHECK( geo.get_num_indices() == 3 );
	}
}
