#include <FWSG/Camera.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestCamera ) {
	using namespace sg;

	// Initial state.
	{
		Camera camera( sf::FloatRect( 0.0f, 0.0f, 100.0f, 100.0f ) );

		BOOST_CHECK( camera.get_transform() == Transform() );
		BOOST_CHECK( camera.get_projection_matrix() == FloatMatrix() );
		BOOST_CHECK( camera.get_combined_matrix() == FloatMatrix() );
		BOOST_CHECK( camera.get_viewport() == sf::FloatRect( 0.0f, 0.0f, 100.0f, 100.0f ) );
	}

	// Basic properties.
	{
		Camera camera( sf::FloatRect( 0.0f, 0.0f, 100.0f, 100.0f ) );

		camera.set_viewport( sf::FloatRect( 1.0f, 2.0f, 3.0f, 4.0f ) );

		BOOST_CHECK( camera.get_viewport() == sf::FloatRect( 1.0f, 2.0f, 3.0f, 4.0f ) );
	}

	// Setup parallel projection camera.
	{
		Camera camera( sf::FloatRect( 0.0f, 0.0f, 100.0f, 100.0f ) );
		
		camera.setup_parallel_projection(
			1.0f, 2.0f, // L R
			3.0f, 4.0f, // B T
			5.0f, 6.0f // N F
		);

		BOOST_CHECK( camera.get_projection_matrix()[ 0] == 2.0f / (2.0f - 1.0f) );
		BOOST_CHECK( camera.get_projection_matrix()[ 1] == 0.0f );
		BOOST_CHECK( camera.get_projection_matrix()[ 2] == 0.0f );
		BOOST_CHECK( camera.get_projection_matrix()[ 3] == 0.0f );

		BOOST_CHECK( camera.get_projection_matrix()[ 4] == 0.0f );
		BOOST_CHECK( camera.get_projection_matrix()[ 5] == 2.0f / (4.0f - 3.0f) );
		BOOST_CHECK( camera.get_projection_matrix()[ 6] == 0.0f );
		BOOST_CHECK( camera.get_projection_matrix()[ 7] == 0.0f );

		BOOST_CHECK( camera.get_projection_matrix()[ 8] == 0.0f );
		BOOST_CHECK( camera.get_projection_matrix()[ 9] == 0.0f );
		BOOST_CHECK( camera.get_projection_matrix()[10] == -2.0f / (6.0f - 5.0f) );
		BOOST_CHECK( camera.get_projection_matrix()[11] == 0.0f );

		BOOST_CHECK( camera.get_projection_matrix()[12] == -((2.0f + 1.0f) / (2.0f - 1.0f)) );
		BOOST_CHECK( camera.get_projection_matrix()[13] == -((4.0f + 3.0f) / (4.0f - 3.0f)) );
		BOOST_CHECK( camera.get_projection_matrix()[14] == -((6.0f + 5.0f) / (6.0f - 5.0f)) );
		BOOST_CHECK( camera.get_projection_matrix()[15] == 1.0f );

		BOOST_CHECK( camera.get_combined_matrix() == camera.get_projection_matrix() );
	}

	// Setup perspective projection camera.
	{
		static const float ASPECT = 50.0f;
		static const float FOV = 90.0f;
		static const float NEAR = 1.0f;
		static const float FAR = 100.0f;

		Camera camera( sf::FloatRect( 0.0f, 0.0f, 100.0f, 100.0f ) );
		
		camera.setup_perspective_projection(
			FOV,
			ASPECT,
			NEAR,
			FAR
		);

		float f = 1.0f / std::tan( (FOV * PI / 180.0f) / 2.0f );

		static const FloatMatrix PROJECTION_MATRIX(
			f / ASPECT, 0.0f, 0.0f, 0.0f,
			0.0f, f, 0.0f, 0.0f,
			0.0f, 0.0f, (FAR + NEAR) / (NEAR - FAR), (2.0f * FAR * NEAR) / (NEAR - FAR),
			0.0f, 0.0f, -1.0f, 0.0f
		);
		
		for(unsigned int i = 0; i < 15; ++i)
		{
			BOOST_CHECK( std::abs( camera.get_projection_matrix()[i] - PROJECTION_MATRIX[i] ) <= 0.000001f );
		}

		BOOST_CHECK( camera.get_combined_matrix() == camera.get_projection_matrix() );
	}

	// Basic properties.
	{
		static const Transform TRANSFORM = Transform(
			sf::Vector3f( 1.0f, 2.0f, 3.0f ),
			sf::Vector3f( 10.0f, 20.0f, 30.0f ),
			sf::Vector3f( 100.0f, 200.0f, 300.0f ),
			sf::Vector3f( 1000.0f, 2000.0f, 3000.0f )
		);

		Camera camera( sf::FloatRect( 0.0f, 0.0f, 100.0f, 100.0f ) );
		camera.set_transform( TRANSFORM );

		BOOST_CHECK( camera.get_transform() == TRANSFORM );
	}

	// Translate camera.
	{
		Camera camera( sf::FloatRect( 0.0f, 0.0f, 100.0f, 100.0f ) );

		camera.translate( sf::Vector3f( 1.0f, 2.0f, 3.0f ) );
		camera.translate( sf::Vector3f( 10.0f, 20.0f, 30.0f ) );

		BOOST_CHECK(
			camera.get_transform() == Transform(
				sf::Vector3f( 11.0f, 22.0f, 33.0f ),
				sf::Vector3f( 0.0f, 0.0f, 0.0f ),
				sf::Vector3f( 1.0f, 1.0f, 1.0f ),
				sf::Vector3f( 0.0f, 0.0f, 0.0f )
			)
		);

		BOOST_CHECK(
			camera.get_combined_matrix() == Transform(
				sf::Vector3f(
					-camera.get_transform().get_translation().x,
					-camera.get_transform().get_translation().y,
					-camera.get_transform().get_translation().z
				),
				sf::Vector3f(
					-camera.get_transform().get_rotation().x,
					-camera.get_transform().get_rotation().y,
					-camera.get_transform().get_rotation().z
				),
				camera.get_transform().get_scale(),
				sf::Vector3f(
					-camera.get_transform().get_origin().x,
					-camera.get_transform().get_origin().y,
					-camera.get_transform().get_origin().z
				)
			).get_matrix()
		);
	}

	// Rotate camera.
	{
		Camera camera( sf::FloatRect( 0.0f, 0.0f, 100.0f, 100.0f ) );

		camera.rotate( sf::Vector3f( 1.0f, 0.0f, 0.0f ) );
		camera.rotate( sf::Vector3f( 0.0f, 2.0f, 0.0f ) );
		camera.rotate( sf::Vector3f( 0.0f, 0.0f, 3.0f ) );

		BOOST_CHECK(
			camera.get_transform() == Transform(
				sf::Vector3f( 0.0f, 0.0f, 0.0f ),
				sf::Vector3f( 1.0f, 2.0f, 3.0f ),
				sf::Vector3f( 1.0f, 1.0f, 1.0f ),
				sf::Vector3f( 0.0f, 0.0f, 0.0f )
			)
		);

		BOOST_CHECK(
			camera.get_combined_matrix() == Transform(
				sf::Vector3f(
					-camera.get_transform().get_translation().x,
					-camera.get_transform().get_translation().y,
					-camera.get_transform().get_translation().z
				),
				sf::Vector3f(
					-camera.get_transform().get_rotation().x,
					-camera.get_transform().get_rotation().y,
					-camera.get_transform().get_rotation().z
				),
				camera.get_transform().get_scale(),
				sf::Vector3f(
					-camera.get_transform().get_origin().x,
					-camera.get_transform().get_origin().y,
					-camera.get_transform().get_origin().z
				)
			).get_matrix()
		);
	}

	// Check a combined matrix.
	{
		Camera camera( sf::FloatRect( 0.0f, 0.0f, 100.0f, 100.0f ) );

		camera.setup_parallel_projection( 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f );
		camera.translate( sf::Vector3f( 1.0f, 2.0f, 3.0f ) );
		camera.rotate( sf::Vector3f( 4.0f, 5.0f, 6.0f ) );

		FloatMatrix expected_matrix = camera.get_projection_matrix();
		expected_matrix.multiply(
			Transform(
				sf::Vector3f(
					-camera.get_transform().get_translation().x,
					-camera.get_transform().get_translation().y,
					-camera.get_transform().get_translation().z
				),
				sf::Vector3f(
					-camera.get_transform().get_rotation().x,
					-camera.get_transform().get_rotation().y,
					-camera.get_transform().get_rotation().z
				),
				camera.get_transform().get_scale(),
				sf::Vector3f(
					-camera.get_transform().get_origin().x,
					-camera.get_transform().get_origin().y,
					-camera.get_transform().get_origin().z
				)
			).get_matrix()
		);

		BOOST_CHECK( camera.get_combined_matrix() == expected_matrix );
	}
}
