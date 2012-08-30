#include "Window.hpp"

#include <FWSG/Step.hpp>
#include <FWSG/Transform.hpp>
#include <FWSG/RenderState.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestStep ) {
	init_test_window();

	sg::BufferObject::Ptr bo( new sg::BufferObject );

	// Initial state.
	{
		sg::Transform trans;
		sg::RenderState r_state;
		sg::FloatMatrix transform_matrix;
		sg::Step step( r_state, transform_matrix, bo );

		BOOST_CHECK( step.get_render_state() == r_state );
		BOOST_CHECK( step.get_transform_matrix() == transform_matrix );
		BOOST_CHECK( step.get_buffer_object() == bo );
	}
}
