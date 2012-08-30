#include <FWSG/Camera.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestCamera ) {
	using namespace sg;

	/*
	// Initial state.
	{
		Camera camera;

		BOOST_CHECK( camera.get_transform() == Transform() );
		BOOST_CHECK( camera.get_field_of_view() == 80.0f );
		BOOST_CHECK( camera.get_projection_mode() == Camera::PERSPECTIVE );
		BOOST_CHECK( camera.get_near_clipping_plane() == 0.1f );
		BOOST_CHECK( camera.get_far_clipping_plane() == 100.0f );
		BOOST_CHECK( camera.get_aspect_ratio() == 1.0f );
	}
	*/

	// Setup parallel projection camera.
	/*
	{
		Camera camera = Camera::create_parallel(
			1.0f, 2.0f,
			3.0f, 4.0f,
			5.0f, 6.0f
		);

		BOOST_CHECK( camera.get_projection_matrix()[0] == 1.0f );
		BOOST_CHECK( camera.get_projection_matrix()[1] == 1.0f );
		BOOST_CHECK( camera.get_projection_matrix()[2] == 1.0f );
		BOOST_CHECK( camera.get_projection_matrix()[3] == 1.0f );
	}
	*/
	// Basic properties.
	/*
	{
		static const Transform TRANSFORM = Transform(
			sf::Vector3f( 1.0f, 2.0f, 3.0f ),
			sf::Vector3f( 10.0f, 20.0f, 30.0f ),
			sf::Vector3f( 100.0f, 200.0f, 300.0f ),
			sf::Vector3f( 1000.0f, 2000.0f, 3000.0f )
		);
		static const float FOV = 80.0f;
		static const Camera::ProjectionMode PROJECTION_MODE = Camera::PARALLEL;
		static const float NEAR_CLIPPING_PLANE = 200.0f;
		static const float FAR_CLIPPING_PLANE = 400.0f;
		static const float ASPECT_RATIO = 100.0f;

		Camera camera;

		camera.set_transform( TRANSFORM );
		camera.set_field_of_view( FOV );
		camera.set_projection_mode( PROJECTION_MODE );
		camera.set_near_clipping_plane( NEAR_CLIPPING_PLANE );
		camera.set_far_clipping_plane( FAR_CLIPPING_PLANE );
		camera.set_aspect_ratio( ASPECT_RATIO );

		BOOST_CHECK( camera.get_transform() == TRANSFORM );
		BOOST_CHECK( camera.get_field_of_view() == FOV );
		BOOST_CHECK( camera.get_projection_mode() == PROJECTION_MODE );
		BOOST_CHECK( camera.get_near_clipping_plane() == NEAR_CLIPPING_PLANE );
		BOOST_CHECK( camera.get_far_clipping_plane() == FAR_CLIPPING_PLANE );
		BOOST_CHECK( camera.get_aspect_ratio() == ASPECT_RATIO );
	}

	// Translate camera.
	{
		Camera camera;

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
	}

	// Rotate camera.
	{
		Camera camera;

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
	}
	*/
}
