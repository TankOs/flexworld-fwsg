#include <FWSG/Transform.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestTransform ) {
	// Initial state.
	{
		sg::Transform trans;

		BOOST_CHECK( trans.get_translation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( trans.get_rotation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( trans.get_scale() == sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( trans.get_origin() == sf::Vector3f( 0, 0, 0 ) );
	}

	// Basic properties.
	{
		sg::Transform trans;

		trans.set_translation( sf::Vector3f( 1, 2, 3 ) );
		trans.set_rotation( sf::Vector3f( 4, 5, 6 ) );
		trans.set_scale( sf::Vector3f( 7, 8, 9 ) );
		trans.set_origin( sf::Vector3f( 10, 20, 30 ) );

		BOOST_CHECK( trans.get_translation() == sf::Vector3f( 1, 2, 3 ) );
		BOOST_CHECK( trans.get_rotation() == sf::Vector3f( 4, 5, 6 ) );
		BOOST_CHECK( trans.get_scale() == sf::Vector3f( 7, 8, 9 ) );
		BOOST_CHECK( trans.get_origin() == sf::Vector3f( 10, 20, 30 ) );
	}

	// Equality.
	{
		sg::Transform a;
		sg::Transform b;

		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 1, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 1, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 1 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 1, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 1, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 1 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 2, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 2, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 2 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		// Origin.
		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 1, 0, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 1, 0 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 1 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );
	}

	// Unequality.
	{
		sg::Transform a;
		sg::Transform b;

		a.set_translation( sf::Vector3f( 1, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 1, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 1 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 1, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 1, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 1 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 2, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 2, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 2 ) );
		a.set_origin( sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		// Origin.
		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 1, 0, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 1, 0 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		a.set_origin( sf::Vector3f( 0, 0, 1 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );
	}
}
