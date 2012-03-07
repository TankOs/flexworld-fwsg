#include <FWSG/Step.hpp>
#include <FWSG/Transform.hpp>

#include <SFML/Graphics.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestStep ) {
	sf::RenderWindow window( sf::VideoMode( 100, 100 ), "-" );

	sg::BufferObject::Ptr bo( new sg::BufferObject );

	// Initial state.
	{
		sg::Transform trans;
		sg::Step step( trans, bo );

		BOOST_CHECK( &step.get_transform() == &trans );
		BOOST_CHECK( step.get_buffer_object() == bo );
	}
}
