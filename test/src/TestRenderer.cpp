#include <FWSG/Renderer.hpp>
#include <FWSG/BufferObject.hpp>

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

	// Create single step.
	{
		sg::Renderer renderer;
		sg::RenderState r_state;
		sg::BufferObject::Ptr buffer_object( new sg::BufferObject );

		// Do in own scope to check auto-removal of the step.
		{
			sg::StepProxy::Ptr step = renderer.create_step( r_state, buffer_object );

			BOOST_CHECK( renderer.get_num_steps() == 1 );
			BOOST_CHECK( renderer.get_num_render_states() == 1 );
		}

		BOOST_CHECK( renderer.get_num_steps() == 0 );
		BOOST_CHECK( renderer.get_num_render_states() == 0 );
	}

	// Create multiple steps.
	{
		sg::Renderer renderer;
		sg::RenderState r_state;
		sg::BufferObject::Ptr buffer_object( new sg::BufferObject );

		// Create two steps within same render state.
		sg::StepProxy::Ptr step0 = renderer.create_step( r_state, buffer_object );
		sg::StepProxy::Ptr step1 = renderer.create_step( r_state, buffer_object );

		BOOST_CHECK( renderer.get_num_steps() == 2 );
		BOOST_CHECK( renderer.get_num_render_states() == 1 );
	}
}