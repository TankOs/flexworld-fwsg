#include <FWSG/Transform.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestTransform ) {
	// Initial state.
	{
		sg::Transform trans;

		BOOST_CHECK( trans.get_translation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( trans.get_rotation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( trans.get_scale() == sf::Vector3f( 1, 1, 1 ) );
	}

	// Basic properties.
	{
		sg::Transform trans;

		trans.set_translation( sf::Vector3f( 1, 2, 3 ) );
		trans.set_rotation( sf::Vector3f( 4, 5, 6 ) );
		trans.set_scale( sf::Vector3f( 7, 8, 9 ) );

		BOOST_CHECK( trans.get_translation() == sf::Vector3f( 1, 2, 3 ) );
		BOOST_CHECK( trans.get_rotation() == sf::Vector3f( 4, 5, 6 ) );
		BOOST_CHECK( trans.get_scale() == sf::Vector3f( 7, 8, 9 ) );
	}

	// Equality.
	{
		sg::Transform a;
		sg::Transform b;

		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 1, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 1, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 1 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 1, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 1, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 1 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 2, 1, 1 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 2, 1 ) );
		BOOST_CHECK( !(a == b) );
		b = a;
		BOOST_CHECK( a == b );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 2 ) );
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
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 1, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 1 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 1, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 1, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 1 ) );
		a.set_scale( sf::Vector3f( 1, 1, 1 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 2, 1, 1 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 2, 1 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );

		a.set_translation( sf::Vector3f( 0, 0, 0 ) );
		a.set_rotation( sf::Vector3f( 0, 0, 0 ) );
		a.set_scale( sf::Vector3f( 1, 1, 2 ) );
		BOOST_CHECK( a != b );
		b = a;
		BOOST_CHECK( !(a != b) );
	}

	// Add.
	{
		sg::Transform a( sf::Vector3f( 1, 2, 3 ), sf::Vector3f( 4, 5, 6 ), sf::Vector3f( 7, 8, 9 ) );
		sg::Transform b( sf::Vector3f( 11, 12, 13 ), sf::Vector3f( 14, 15, 16 ), sf::Vector3f( 17, 18, 19 ) );

		sg::Transform c = a + b;

		BOOST_CHECK( c.get_translation() == sf::Vector3f( 12, 14, 16 ) );
		BOOST_CHECK( c.get_rotation() == sf::Vector3f( 18, 20, 22 ) );
		BOOST_CHECK( c.get_scale() == sf::Vector3f( 119, 144, 171 ) );
	}
}
