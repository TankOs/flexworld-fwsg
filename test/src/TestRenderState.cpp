#include <FWSG/RenderState.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <boost/test/unit_test.hpp>
#include <memory>

BOOST_AUTO_TEST_CASE( TestRenderState ) {
	sf::RenderWindow window( sf::VideoMode( 100, 100 ), "Unittest" );

	// Initial state.
	{
		sg::RenderState state;

		BOOST_CHECK( state.texture == false );
		BOOST_CHECK( state.wireframe == false );
		BOOST_CHECK( state.depth_test == false );
		BOOST_CHECK( state.cull == false );
	}

	// Equality.
	{
		std::shared_ptr<sf::Texture> texture( new sf::Texture );

		{
			sg::RenderState first;
			sg::RenderState second;

			BOOST_CHECK( first == second );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.texture = texture;
			second.texture = texture;

			BOOST_CHECK( first == second );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.wireframe = !first.wireframe;
			second.wireframe = !second.wireframe;

			BOOST_CHECK( first == second );
		}
	}
}
