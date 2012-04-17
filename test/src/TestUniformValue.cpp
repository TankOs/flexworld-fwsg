#include <FWSG/Uniform1fValue.hpp>
#include <FWSG/Uniform2fValue.hpp>
#include <FWSG/Uniform3fValue.hpp>
#include <FWSG/Uniform4fValue.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestUniform1fValue ) {
	// Initial states.
	{
		sg::Uniform1fValue f_solo( 1337 );
		sg::Uniform2fValue f_vec2( 222 );
		sg::Uniform3fValue f_vec3( 333 );
		sg::Uniform4fValue f_vec4( 444 );

		BOOST_CHECK( f_solo.get_location() == 1337 );
		BOOST_CHECK( f_solo.get() == 0.0f );

		BOOST_CHECK( f_vec2.get_location() == 222 );
		BOOST_CHECK( f_vec2.get_x() == 0.0f );
		BOOST_CHECK( f_vec2.get_y() == 0.0f );

		BOOST_CHECK( f_vec3.get_location() == 333 );
		BOOST_CHECK( f_vec3.get_x() == 0.0f );
		BOOST_CHECK( f_vec3.get_y() == 0.0f );
		BOOST_CHECK( f_vec3.get_z() == 0.0f );

		BOOST_CHECK( f_vec4.get_location() == 444 );
		BOOST_CHECK( f_vec4.get_x() == 0.0f );
		BOOST_CHECK( f_vec4.get_y() == 0.0f );
		BOOST_CHECK( f_vec4.get_z() == 0.0f );
		BOOST_CHECK( f_vec4.get_w() == 0.0f );
	}

	// Set.
	{
		sg::Uniform1fValue f_solo( 1337 );
		sg::Uniform2fValue f_vec2( 222 );
		sg::Uniform3fValue f_vec3( 333 );
		sg::Uniform4fValue f_vec4( 444 );

		f_solo.set( 5.0f );
		f_vec2.set( 1.0f, 2.0f );
		f_vec3.set( 1.0f, 2.0f, 3.0f );
		f_vec4.set( 1.0f, 2.0f, 3.0f, 4.0f );

		BOOST_CHECK( f_solo.get() == 5.0f );

		BOOST_CHECK( f_vec2.get_x() == 1.0f );
		BOOST_CHECK( f_vec2.get_y() == 2.0f );

		BOOST_CHECK( f_vec3.get_x() == 1.0f );
		BOOST_CHECK( f_vec3.get_y() == 2.0f );
		BOOST_CHECK( f_vec3.get_z() == 3.0f );

		BOOST_CHECK( f_vec4.get_x() == 1.0f );
		BOOST_CHECK( f_vec4.get_y() == 2.0f );
		BOOST_CHECK( f_vec4.get_z() == 3.0f );
		BOOST_CHECK( f_vec4.get_w() == 4.0f );
	}
}
