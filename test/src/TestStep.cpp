#include <FWSG/Step.hpp>

#include <SFML/Graphics.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestStep ) {
	sf::RenderWindow window( sf::VideoMode( 100, 100 ), "-" );

	sg::BufferObject::Ptr bo( new sg::BufferObject );

	// Initial state.
	{
		sg::Step step( bo );

		BOOST_CHECK( step.get_translation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( step.get_rotation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( step.get_scale() == sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( step.get_buffer_object() == bo );
	}

	// Basic properties.
	{
		const sf::Vector3f TRANSLATION( 5, 10, 15 );
		const sf::Vector3f ROTATION( 20, 30, 40 );
		const sf::Vector3f SCALE( 1, 2, 3 );

		sg::Step step( bo );

		step.set_translation( TRANSLATION );
		step.set_rotation( ROTATION );
		step.set_scale( SCALE );

		BOOST_CHECK( step.get_translation() == TRANSLATION );
		BOOST_CHECK( step.get_rotation() == ROTATION );
		BOOST_CHECK( step.get_scale() == SCALE );
	}
}
