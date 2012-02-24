#include <FWSG/StepProxy.hpp>
#include <FWSG/Step.hpp>
#include <FWSG/Renderer.hpp>
#include <FWSG/BufferObject.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestStepProxy ) {
	sg::Renderer renderer;
	sg::BufferObject::Ptr bo( new sg::BufferObject );

	// Initial state.
	{
		sg::Step::Ptr step( new sg::Step( bo ) );
		sg::StepProxy proxy( step, renderer, false );

		BOOST_CHECK( proxy.get_step() == step );
		BOOST_CHECK( &proxy.get_renderer() == &renderer );
	}

	// Operations.
	{
		sg::Step::Ptr step( new sg::Step( bo ) );
		sg::StepProxy proxy( step, renderer, false );

		BOOST_CHECK( step->get_translation() == sf::Vector3f( 0, 0, 0 ) );
		proxy.set_translation( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( step->get_translation() == sf::Vector3f( 1, 1, 1 ) );

		BOOST_CHECK( step->get_rotation() == sf::Vector3f( 0, 0, 0 ) );
		proxy.set_rotation( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( step->get_rotation() == sf::Vector3f( 1, 1, 1 ) );

		BOOST_CHECK( step->get_scale() == sf::Vector3f( 1, 1, 1 ) );
		proxy.set_scale( sf::Vector3f( 2, 2, 2 ) );
		BOOST_CHECK( step->get_scale() == sf::Vector3f( 2, 2, 2 ) );
	}
}
