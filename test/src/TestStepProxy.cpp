#include <FWSG/StepProxy.hpp>
#include <FWSG/Step.hpp>
#include <FWSG/Renderer.hpp>
#include <FWSG/BufferObject.hpp>
#include <FWSG/Transform.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestStepProxy ) {
	sg::Renderer renderer;
	sg::BufferObject::Ptr bo( new sg::BufferObject );
	sg::Transform trans;

	// Initial state.
	{
		sg::Step::Ptr step( new sg::Step( trans, bo ) );
		sg::StepProxy proxy( step, renderer, false );

		BOOST_CHECK( proxy.get_step() == step );
		BOOST_CHECK( &proxy.get_renderer() == &renderer );
	}
}
