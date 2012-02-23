#include <FWSG/RenderState.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestRenderState ) {
	// Initial state.
	{
		sg::RenderState state;

		BOOST_CHECK( state.texture == false );
		BOOST_CHECK( state.wireframe == false );
		BOOST_CHECK( state.depth_test == false );
		BOOST_CHECK( state.cull == false );
	}
}
