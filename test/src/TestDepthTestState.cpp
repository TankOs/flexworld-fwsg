#include <FWSG/DepthTestState.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestDepthTestState ) {
	// Initial state.
	{
		BOOST_CHECK( sg::DepthTestState::TYPE_ID == sg::State::DEPTH_TEST );

		{
			sg::DepthTestState state( true );
			BOOST_CHECK( state.get_type() == sg::DepthTestState::TYPE_ID );
			BOOST_CHECK( state.is_set() == true );
		}
		{
			sg::DepthTestState state( false );
			BOOST_CHECK( state.get_type() == sg::DepthTestState::TYPE_ID );
			BOOST_CHECK( state.is_set() == false );
		}
	}
}
