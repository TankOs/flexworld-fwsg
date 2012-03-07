#include <FWSG/BackfaceCullingState.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestBackfaceCullingState ) {
	// Initial state.
	{
		BOOST_CHECK( sg::BackfaceCullingState::TYPE_ID == sg::State::BACKFACE_CULLING );

		{
			sg::BackfaceCullingState state( true );
			BOOST_CHECK( state.get_type() == sg::BackfaceCullingState::TYPE_ID );
			BOOST_CHECK( state.is_set() == true );
		}
		{
			sg::BackfaceCullingState state( false );
			BOOST_CHECK( state.get_type() == sg::BackfaceCullingState::TYPE_ID );
			BOOST_CHECK( state.is_set() == false );
		}
	}
}
