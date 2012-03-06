#include <FWSG/BufferObject.hpp>
#include <FWSG/TriangleGeometry.hpp>

#include <SFML/Graphics.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestBufferObject ) {
	sf::RenderWindow window( sf::VideoMode( 100, 100 ), "-" );

	// Initial state.
	{
		sg::BufferObject bo;

		BOOST_CHECK( bo.get_num_vertices() == 0 );
	}

	// Build geometry for testing.
	sg::TriangleGeometry tri_geo;

	{
		std::vector<sg::Vertex> vertices;
		vertices.push_back( sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ) ) ); // Not unique!
		vertices.push_back( sg::Vertex( sf::Vector3f( 0, 0, 1 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ) ) );
		vertices.push_back( sg::Vertex( sf::Vector3f( 1, 0, 1 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ) ) ); // Not unique!
		vertices.push_back( sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ) ) ); // Not unique!
		vertices.push_back( sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ) ) );
		vertices.push_back( sg::Vertex( sf::Vector3f( 1, 0, 1 ), sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ) ) ); // Not unique!

		for( std::size_t idx = 0; idx < vertices.size(); idx += 3 ) {
			tri_geo.add_triangle(
				vertices[idx + 0],
				vertices[idx + 1],
				vertices[idx + 2],
				true
			);
		}
	}

	// Client-side buffer object.
	{
		sg::BufferObject client_bo( sg::BufferObject::EVERYTHING, true );

		BOOST_CHECK( client_bo.is_client_buffer() == true );

		client_bo.load( tri_geo );
		BOOST_CHECK( client_bo.get_num_vertices() == 6 );
	}

	// GPU-side buffer object.
	{
		sg::BufferObject gpu_bo( sg::BufferObject::EVERYTHING, false );

		BOOST_CHECK( gpu_bo.is_client_buffer() == false );

		gpu_bo.load( tri_geo );
		BOOST_CHECK( gpu_bo.get_num_vertices() == 6 );
	}
}
