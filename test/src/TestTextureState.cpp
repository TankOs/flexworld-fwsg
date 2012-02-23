#include <FWSG/TextureState.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestTextureState ) {
	sf::RenderWindow window( sf::VideoMode( 100, 100 ), "Unittest" );

	BOOST_CHECK( sg::TextureState::TYPE_ID == sg::State::TEXTURE );

	// Initial state.
	{
		std::shared_ptr<sf::Texture> texture( new sf::Texture );

		sg::TextureState tex_state( texture );

		BOOST_CHECK( tex_state.get_type() == sg::TextureState::TYPE_ID );
		BOOST_CHECK( tex_state.get_texture() == texture );
	}
}
