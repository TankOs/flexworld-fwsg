#include <FWSG/WireframeState.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestWireframeState ) {
	// Initial state.
	{
		{
			sg::WireframeState state( true );
			BOOST_CHECK( state.get_type() == sg::State::WIREFRAME );
			BOOST_CHECK( state.is_set() == true );
		}
		{
			sg::WireframeState state( false );
			BOOST_CHECK( state.get_type() == sg::State::WIREFRAME );
			BOOST_CHECK( state.is_set() == false );
		}
	}
}
