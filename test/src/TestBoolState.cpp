#include <FWSG/BoolState.hpp>

#include <boost/test/unit_test.hpp>

class Impl : public sg::BoolState {
	public:
		Impl( Type type, bool value ) :
			BoolState( type, value )
		{
		}

	private:
};

BOOST_AUTO_TEST_CASE( TestBoolState ) {
	// Initial state.
	{
		Impl state0( sg::State::WIREFRAME, false );
		Impl state1( sg::State::WIREFRAME, true );
		Impl state2( sg::State::DEPTH_TEST, false );
		Impl state3( sg::State::DEPTH_TEST, true );

		BOOST_CHECK( state0.is_set() == false );
		BOOST_CHECK( state0.get_type() == sg::State::WIREFRAME );
		BOOST_CHECK( state1.is_set() == true );
		BOOST_CHECK( state1.get_type() == sg::State::WIREFRAME );
		BOOST_CHECK( state2.is_set() == false );
		BOOST_CHECK( state2.get_type() == sg::State::DEPTH_TEST );
		BOOST_CHECK( state3.is_set() == true );
		BOOST_CHECK( state3.get_type() == sg::State::DEPTH_TEST );
	}
}
