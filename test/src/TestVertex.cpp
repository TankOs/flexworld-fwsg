#include <FWSG/Vertex.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestVertex ) {
	// Initial state.
	{
		sg::Vertex vertex;

		BOOST_CHECK( vertex.vector == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( vertex.normal == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( vertex.uv == sf::Vector2f( 0, 0 ) );
		BOOST_CHECK( vertex.color == sf::Color::White );
	}

	// Ctor.
	{
		const sf::Vector3f VECTOR( 1, 2, 3 );
		const sf::Vector3f NORMAL( 10, 11, 12 );
		const sf::Vector2f UV( 20, 21 );
		const sf::Color COLOR( 30, 31, 32, 33 );

		{
			sg::Vertex vertex( VECTOR, NORMAL, UV, COLOR );

			BOOST_CHECK( vertex.vector == VECTOR );
			BOOST_CHECK( vertex.normal == NORMAL );
			BOOST_CHECK( vertex.uv == UV );
			BOOST_CHECK( vertex.color == COLOR );
		}
		{
			sg::Vertex vertex( VECTOR, UV );

			BOOST_CHECK( vertex.vector == VECTOR );
			BOOST_CHECK( vertex.normal == sf::Vector3f( 0, 0, 0 ) );
			BOOST_CHECK( vertex.uv == UV );
			BOOST_CHECK( vertex.color == sf::Color::White );
		}
	}

	// Equality.
	{
		BOOST_CHECK( sg::Vertex() == sg::Vertex() );

		sg::Vertex first( sf::Vector3f( 1, 2, 3 ), sf::Vector3f( 10, 11, 12 ), sf::Vector2f( 20, 21 ), sf::Color::Red );
		sg::Vertex second( sf::Vector3f( 1, 2, 3 ), sf::Vector3f( 10, 11, 12 ), sf::Vector2f( 20, 21 ), sf::Color::Red );

		BOOST_CHECK( first == second );

		second.vector.x += 1.0f;
		BOOST_CHECK( !(first == second) );
		second = first;

		second.normal.x += 1.0f;
		BOOST_CHECK( !(first == second) );
		second = first;

		second.uv.x += 1.0f;
		BOOST_CHECK( !(first == second) );
		second = first;

		second.color.r = static_cast<sf::Uint8>( second.color.r + 1 );
		BOOST_CHECK( !(first == second) );
		second = first;
	}

	// Unequality.
	{
		sg::Vertex first( sf::Vector3f( 1, 2, 3 ), sf::Vector3f( 10, 11, 12 ), sf::Vector2f( 20, 21 ), sf::Color::Red );
		sg::Vertex second = first;

		second.vector = sf::Vector3f( 0, 2, 3 );
		BOOST_CHECK( first != second );
		second.vector = sf::Vector3f( 1, 0, 3 );
		BOOST_CHECK( first != second );
		second.vector = sf::Vector3f( 1, 2, 0 );
		BOOST_CHECK( first != second );

		second = first;
		second.normal = sf::Vector3f( 0, 11, 12 );
		BOOST_CHECK( first != second );
		second.normal = sf::Vector3f( 10, 0, 12 );
		BOOST_CHECK( first != second );
		second.normal = sf::Vector3f( 10, 11, 0 );
		BOOST_CHECK( first != second );

		second = first;
		second.uv = sf::Vector2f( 0, 21 );
		BOOST_CHECK( first != second );
		second.uv = sf::Vector2f( 20, 0 );
		BOOST_CHECK( first != second );

		second = first;
		second.color = sf::Color::Yellow;
		BOOST_CHECK( first != second );
	}
}
