#include <FWSG/Triangle.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestTriangle ) {
	// Initial state.
	{
		sg::Triangle tri;

		BOOST_CHECK( tri.a == 0 );
		BOOST_CHECK( tri.b == 0 );
		BOOST_CHECK( tri.c == 0 );
	}

	// Ctor.
	{
		sg::Triangle tri( 1, 2, 3 );

		BOOST_CHECK( tri.a == 1 );
		BOOST_CHECK( tri.b == 2 );
		BOOST_CHECK( tri.c == 3 );
	}

	// Equality.
	{
		sg::Triangle fst;
		sg::Triangle snd;

		BOOST_CHECK( fst == snd );

		fst = sg::Triangle( 1, 2, 3 );
		snd = sg::Triangle( 1, 2, 3 );
		BOOST_CHECK( fst == snd );

		fst = sg::Triangle( 0, 2, 3 );
		snd = sg::Triangle( 1, 2, 3 );
		BOOST_CHECK( !(fst == snd) );
		BOOST_CHECK( !(snd == fst) );

		fst = sg::Triangle( 1, 0, 3 );
		snd = sg::Triangle( 1, 2, 3 );
		BOOST_CHECK( !(fst == snd) );
		BOOST_CHECK( !(snd == fst) );

		fst = sg::Triangle( 1, 2, 0 );
		snd = sg::Triangle( 1, 2, 3 );
		BOOST_CHECK( !(fst == snd) );
		BOOST_CHECK( !(snd == fst) );
	}

	// Unequality.
	{
		sg::Triangle fst( 0, 2, 3 );
		sg::Triangle snd( 1, 2, 3 );
		BOOST_CHECK( fst != snd );
		BOOST_CHECK( snd != fst );

		fst = sg::Triangle( 1, 0, 3 );
		snd = sg::Triangle( 1, 2, 3 );
		BOOST_CHECK( fst != snd );
		BOOST_CHECK( snd != fst );

		fst = sg::Triangle( 1, 2, 0 );
		snd = sg::Triangle( 1, 2, 3 );
		BOOST_CHECK( fst != snd );
		BOOST_CHECK( snd != fst );

		fst = snd;
		BOOST_CHECK( !(fst != snd) );
		BOOST_CHECK( !(snd != fst) );
	}
}
