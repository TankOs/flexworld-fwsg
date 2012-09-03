#include <FWSG/Matrix.hpp>

#include <boost/test/unit_test.hpp>
#include <cmath>

bool tolerance_check( const sg::Matrix<float>& m0, const sg::Matrix<float>& m1 ) {
	for( std::size_t idx = 0; idx < 16; ++idx ) {
		if( std::abs( m0[idx] - m1[idx] ) >= 0.0001f ) {
			return false;
		}
	}

	return true;
}

BOOST_AUTO_TEST_CASE( TestMatrix ) {
	using namespace sg;

	// Initial state.
	{
		Matrix<float> matrix;

		BOOST_CHECK( matrix[ 0] == 1.0f );
		BOOST_CHECK( matrix[ 1] == 0.0f );
		BOOST_CHECK( matrix[ 2] == 0.0f );
		BOOST_CHECK( matrix[ 3] == 0.0f );

		BOOST_CHECK( matrix[ 4] == 0.0f );
		BOOST_CHECK( matrix[ 5] == 1.0f );
		BOOST_CHECK( matrix[ 6] == 0.0f );
		BOOST_CHECK( matrix[ 7] == 0.0f );

		BOOST_CHECK( matrix[ 8] == 0.0f );
		BOOST_CHECK( matrix[ 9] == 0.0f );
		BOOST_CHECK( matrix[10] == 1.0f );
		BOOST_CHECK( matrix[11] == 0.0f );

		BOOST_CHECK( matrix[12] == 0.0f );
		BOOST_CHECK( matrix[13] == 0.0f );
		BOOST_CHECK( matrix[14] == 0.0f );
		BOOST_CHECK( matrix[15] == 1.0f );
	}
	{
		Matrix<float> matrix(
			1, 5, 9, 13,
			2, 6, 10, 14,
			3, 7, 11, 15,
			4, 8, 12, 16
		);

		BOOST_CHECK( matrix[ 0] == 1.0f );
		BOOST_CHECK( matrix[ 1] == 2.0f );
		BOOST_CHECK( matrix[ 2] == 3.0f );
		BOOST_CHECK( matrix[ 3] == 4.0f );

		BOOST_CHECK( matrix[ 4] == 5.0f );
		BOOST_CHECK( matrix[ 5] == 6.0f );
		BOOST_CHECK( matrix[ 6] == 7.0f );
		BOOST_CHECK( matrix[ 7] == 8.0f );

		BOOST_CHECK( matrix[ 8] == 9.0f );
		BOOST_CHECK( matrix[ 9] == 10.0f );
		BOOST_CHECK( matrix[10] == 11.0f );
		BOOST_CHECK( matrix[11] == 12.0f );

		BOOST_CHECK( matrix[12] == 13.0f );
		BOOST_CHECK( matrix[13] == 14.0f );
		BOOST_CHECK( matrix[14] == 15.0f );
		BOOST_CHECK( matrix[15] == 16.0f );
	}

	// Equality.
	{
		for( std::size_t idx = 0; idx < 16; ++idx ) {
			Matrix<float> m0( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
			Matrix<float> m1( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 );

			m0[idx] = 1;
			m1[idx] = 1;
			BOOST_CHECK( m0 == m1 );

			m0[idx] = 1;
			m1[idx] = 0;
			BOOST_CHECK( !(m0 == m1) );

			m0[idx] = 0;
			m1[idx] = 1;
			BOOST_CHECK( !(m0 == m1) );
		}
	}

	// Equality.
	{
		for( std::size_t idx = 0; idx < 16; ++idx ) {
			Matrix<float> m0( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
			Matrix<float> m1( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 );

			m1[idx] = 1;
			BOOST_CHECK( m0 != m1 );
		}
	}

	// Identity.
	{
		Matrix<float> matrix;

		for( std::size_t idx = 0; idx < 16; ++idx ) {
			matrix.values[idx] = 999;
		}

		matrix.reset();

		BOOST_CHECK( matrix[ 0] == 1.0f );
		BOOST_CHECK( matrix[ 1] == 0.0f );
		BOOST_CHECK( matrix[ 2] == 0.0f );
		BOOST_CHECK( matrix[ 3] == 0.0f );

		BOOST_CHECK( matrix[ 4] == 0.0f );
		BOOST_CHECK( matrix[ 5] == 1.0f );
		BOOST_CHECK( matrix[ 6] == 0.0f );
		BOOST_CHECK( matrix[ 7] == 0.0f );

		BOOST_CHECK( matrix[ 8] == 0.0f );
		BOOST_CHECK( matrix[ 9] == 0.0f );
		BOOST_CHECK( matrix[10] == 1.0f );
		BOOST_CHECK( matrix[11] == 0.0f );

		BOOST_CHECK( matrix[12] == 0.0f );
		BOOST_CHECK( matrix[13] == 0.0f );
		BOOST_CHECK( matrix[14] == 0.0f );
		BOOST_CHECK( matrix[15] == 1.0f );
	}

	// Multiply matrices.
	{
		Matrix<float> m0(
			1, 5, 9, 13,
			2, 6, 10, 14,
			3, 7, 11, 15,
			4, 8, 12, 16
		);

		Matrix<float> m1(
			4, 8, 12, 16,
			3, 7, 11, 15,
			2, 6, 10, 14,
			1, 5, 9, 13
		);

		m0.multiply( m1 );

		BOOST_CHECK( m0[ 0] == 50.0f );
		BOOST_CHECK( m0[ 1] == 60.0f );
		BOOST_CHECK( m0[ 2] == 70.0f );
		BOOST_CHECK( m0[ 3] == 80.0f );

		BOOST_CHECK( m0[ 4] == 162.0f );
		BOOST_CHECK( m0[ 5] == 188.0f );
		BOOST_CHECK( m0[ 6] == 214.0f );
		BOOST_CHECK( m0[ 7] == 240.0f );

		BOOST_CHECK( m0[ 8] == 274.0f );
		BOOST_CHECK( m0[ 9] == 316.0f );
		BOOST_CHECK( m0[10] == 358.0f );
		BOOST_CHECK( m0[11] == 400.0f );

		BOOST_CHECK( m0[12] == 386.0f );
		BOOST_CHECK( m0[13] == 444.0f );
		BOOST_CHECK( m0[14] == 502.0f );
		BOOST_CHECK( m0[15] == 560.0f );
	}

	// Translate.
	{
		Matrix<float> matrix;

		matrix.translate( sf::Vector3f( 10.0f, 20.0f, 30.0f ) );

		BOOST_CHECK( matrix[ 0] == 1.0f );
		BOOST_CHECK( matrix[ 1] == 0.0f );
		BOOST_CHECK( matrix[ 2] == 0.0f );
		BOOST_CHECK( matrix[ 3] == 0.0f );

		BOOST_CHECK( matrix[ 4] == 0.0f );
		BOOST_CHECK( matrix[ 5] == 1.0f );
		BOOST_CHECK( matrix[ 6] == 0.0f );
		BOOST_CHECK( matrix[ 7] == 0.0f );

		BOOST_CHECK( matrix[ 8] == 0.0f );
		BOOST_CHECK( matrix[ 9] == 0.0f );
		BOOST_CHECK( matrix[10] == 1.0f );
		BOOST_CHECK( matrix[11] == 0.0f );

		BOOST_CHECK( matrix[12] == 10.0f );
		BOOST_CHECK( matrix[13] == 20.0f );
		BOOST_CHECK( matrix[14] == 30.0f );
		BOOST_CHECK( matrix[15] == 1.0f );

		matrix.translate( sf::Vector3f( 10.0f, 20.0f, 30.0f ) );

		BOOST_CHECK( matrix[ 0] == 1.0f );
		BOOST_CHECK( matrix[ 1] == 0.0f );
		BOOST_CHECK( matrix[ 2] == 0.0f );
		BOOST_CHECK( matrix[ 3] == 0.0f );

		BOOST_CHECK( matrix[ 4] == 0.0f );
		BOOST_CHECK( matrix[ 5] == 1.0f );
		BOOST_CHECK( matrix[ 6] == 0.0f );
		BOOST_CHECK( matrix[ 7] == 0.0f );

		BOOST_CHECK( matrix[ 8] == 0.0f );
		BOOST_CHECK( matrix[ 9] == 0.0f );
		BOOST_CHECK( matrix[10] == 1.0f );
		BOOST_CHECK( matrix[11] == 0.0f );

		BOOST_CHECK( matrix[12] == 20.0f );
		BOOST_CHECK( matrix[13] == 40.0f );
		BOOST_CHECK( matrix[14] == 60.0f );
		BOOST_CHECK( matrix[15] == 1.0f );
	}

	// Rotate.
	{
		Matrix<float> pitch_rot_matrix(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, +std::cos( 15.0f * PI / 180.0f ), +std::sin( 15.0f * PI / 180.0f ), 0.0f,
			0.0f, -std::sin( 15.0f * PI / 180.0f ), +std::cos( 15.0f * PI / 180.0f ), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		Matrix<float> yaw_rot_matrix(
			std::cos( 30.0f * PI / 180.0f ), 0.0f, -std::sin( 30.0f * PI / 180.0f ), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			std::sin( 30.0f * PI / 180.0f ), 0.0f, std::cos( 30.0f * PI / 180.0f ), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		Matrix<float> roll_rot_matrix(
			std::cos( 90.0f * PI / 180.0f ), std::sin( 90.0f * PI / 180.0f ), 0.0f, 0.0f,
			-std::sin( 90.0f * PI / 180.0f ), std::cos( 90.0f * PI / 180.0f ), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		Matrix<float> matrix;

		matrix.rotate( sf::Vector3f( 15.0f, 0.0f, 0.0f ) );
		BOOST_CHECK( tolerance_check( matrix, pitch_rot_matrix ) == true );
		matrix.reset();

		matrix.rotate( sf::Vector3f( 0.0f, 30.0f, 0.0f ) );
		BOOST_CHECK( tolerance_check( matrix, yaw_rot_matrix ) == true );
		matrix.reset();

		matrix.rotate( sf::Vector3f( 0.0f, 0.0f, 90.0f ) );
		BOOST_CHECK( tolerance_check( matrix, roll_rot_matrix ) == true );
		matrix.reset();

		matrix.rotate( sf::Vector3f( 15.0f, 0.0f, 0.0f ) );
		matrix.rotate( sf::Vector3f( 0.0f, 30.0f, 0.0f ) );
		matrix.rotate( sf::Vector3f( 0.0f, 0.0f, 90.0f ) );

		pitch_rot_matrix.multiply( yaw_rot_matrix );
		pitch_rot_matrix.multiply( roll_rot_matrix );

		BOOST_CHECK( tolerance_check( matrix, pitch_rot_matrix ) == true );
	}

	// Scale.
	{
		Matrix<float> matrix(
			 1.0f,  2.0f,  3.0f,  4.0f,
			 5.0f,  6.0f,  7.0f,  8.0f,
			 9.0f, 10.0f, 11.0f, 12.0f,
			13.0f, 14.0f, 15.0f, 16.0f
		);

		matrix.scale( sf::Vector3f( 10.0f, 100.0f, 1000.0f ) );

		BOOST_CHECK(
			matrix == Matrix<float>(
				10.0f, 200.0f, 3000.0f, 4.0f,
				50.0f, 600.0f, 7000.0f, 8.0f,
				90.0f, 1000.0f, 11000.0f, 12.0f,
				130.0f, 1400.0f, 15000.0f, 16.0f
			)
		);
	}
}
