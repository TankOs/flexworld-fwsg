#include <FWSG/Renderer.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestRenderer ) {
	sf::RenderWindow window( sf::VideoMode( 100, 100 ), "Unittest" );

	// Initial state.
	{
		sg::Renderer renderer;

		BOOST_CHECK( renderer.get_num_steps() == 0 );
		BOOST_CHECK( renderer.get_num_render_states() == 0 );
	}

	// Create steps.
	{
	}
}
