#include <FWSG/BufferObject.hpp>

#include <SFML/Graphics.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestBufferObject ) {
	sf::RenderWindow window( sf::VideoMode( 100, 100 ), "-" );

	// Initial state.
	{
		sg::BufferObject bo;

		BOOST_CHECK( bo.get_num_prepared_vertices() == 0 );
		BOOST_CHECK( bo.get_num_uploaded_vertices() == 0 );
		BOOST_CHECK( bo.is_upload_needed() == false );
	}

	// Add vertices.
	{
		// Vertex vectors only.
		{
			sg::BufferObject bo( sg::BufferObject::VERTICES_ONLY );

			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 1, 2, 3 ), sf::Vector2f( 100, 200 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 1, 2, 3 ), sf::Vector2f( 101, 201 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector3f( 1, 2, 3 ), sf::Vector2f( 102, 202 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 1 ), sf::Vector3f( 1, 2, 3 ), sf::Vector2f( 103, 203 ) ) );

			BOOST_CHECK( bo.get_num_prepared_vertices() == 4 );
			BOOST_CHECK( bo.get_num_uploaded_vertices() == 0 );

			BOOST_CHECK( bo.get_prepared_vertex( 0 ) == sg::Vertex( sf::Vector3f( 0, 0, 0 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 1 ) == sg::Vertex( sf::Vector3f( 1, 0, 0 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 2 ) == sg::Vertex( sf::Vector3f( 0, 1, 0 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 3 ) == sg::Vertex( sf::Vector3f( 0, 0, 1 ) ) );
		}

		// Vectors + normals.
		{
			sg::BufferObject bo( sg::BufferObject::NORMALS );

			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 1, 2, 3 ), sf::Vector2f( 100, 200 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 4, 5, 6 ), sf::Vector2f( 101, 201 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector3f( 7, 8, 9 ), sf::Vector2f( 102, 202 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 1 ), sf::Vector3f( 10, 11, 12 ), sf::Vector2f( 103, 203 ) ) );

			BOOST_CHECK( bo.get_num_prepared_vertices() == 4 );
			BOOST_CHECK( bo.get_num_uploaded_vertices() == 0 );

			BOOST_CHECK( bo.get_prepared_vertex( 0 ) == sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 1, 2, 3 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 1 ) == sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 4, 5, 6 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 2 ) == sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector3f( 7, 8, 9 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 3 ) == sg::Vertex( sf::Vector3f( 0, 0, 1 ), sf::Vector3f( 10, 11, 12 ) ) );
		}
		// Vectors + texture coordinates.
		{
			sg::BufferObject bo( sg::BufferObject::TEX_COORDS );

			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 1, 2, 3 ), sf::Vector2f( 100, 200 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 4, 5, 6 ), sf::Vector2f( 101, 201 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector3f( 7, 8, 9 ), sf::Vector2f( 102, 202 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 1 ), sf::Vector3f( 10, 11, 12 ), sf::Vector2f( 103, 203 ) ) );

			BOOST_CHECK( bo.get_num_prepared_vertices() == 4 );
			BOOST_CHECK( bo.get_num_uploaded_vertices() == 0 );

			BOOST_CHECK( bo.get_prepared_vertex( 0 ) == sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 0, 0, 0 ), sf::Vector2f( 100, 200 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 1 ) == sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 0, 0, 0 ), sf::Vector2f( 101, 201 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 2 ) == sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector3f( 0, 0, 0 ), sf::Vector2f( 102, 202 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 3 ) == sg::Vertex( sf::Vector3f( 0, 0, 1 ), sf::Vector3f( 0, 0, 0 ), sf::Vector2f( 103, 203 ) ) );
		}
		// Vectors + normals + texture coordinates.
		{
			sg::BufferObject bo( sg::BufferObject::NORMALS | sg::BufferObject::TEX_COORDS );

			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 1, 2, 3 ), sf::Vector2f( 100, 200 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 4, 5, 6 ), sf::Vector2f( 101, 201 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector3f( 7, 8, 9 ), sf::Vector2f( 102, 202 ) ) );
			bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 1 ), sf::Vector3f( 10, 11, 12 ), sf::Vector2f( 103, 203 ) ) );

			BOOST_CHECK( bo.get_num_prepared_vertices() == 4 );
			BOOST_CHECK( bo.get_num_uploaded_vertices() == 0 );

			BOOST_CHECK( bo.get_prepared_vertex( 0 ) == sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 1, 2, 3 ), sf::Vector2f( 100, 200 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 1 ) == sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 4, 5, 6 ), sf::Vector2f( 101, 201 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 2 ) == sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector3f( 7, 8, 9 ), sf::Vector2f( 102, 202 ) ) );
			BOOST_CHECK( bo.get_prepared_vertex( 3 ) == sg::Vertex( sf::Vector3f( 0, 0, 1 ), sf::Vector3f( 10, 11, 12 ), sf::Vector2f( 103, 203 ) ) );
		}
	}

	// Upload.
	{
		sg::BufferObject bo;

		bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector3f( 1, 2, 3 ), sf::Vector2f( 100, 200 ) ) );
		bo.add_vertex( sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector3f( 4, 5, 6 ), sf::Vector2f( 101, 201 ) ) );
		bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector3f( 7, 8, 9 ), sf::Vector2f( 102, 202 ) ) );
		bo.add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 1 ), sf::Vector3f( 10, 11, 12 ), sf::Vector2f( 103, 203 ) ) );

		bo.upload();

		BOOST_CHECK( bo.get_num_prepared_vertices() == 0 );
		BOOST_CHECK( bo.get_num_uploaded_vertices() == 4 );
	}
}
