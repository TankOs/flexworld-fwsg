#include "Window.hpp"

#include <FWSG/RenderState.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/OpenGL.hpp>
#include <boost/test/unit_test.hpp>
#include <memory>

BOOST_AUTO_TEST_CASE( TestRenderState ) {
	init_test_window();

	// Initial state.
	{
		sg::RenderState state;

		BOOST_CHECK( state.min_filter = GL_LINEAR );
		BOOST_CHECK( state.mag_filter = GL_LINEAR );
		BOOST_CHECK( state.texture == false );
		BOOST_CHECK( state.wireframe == false );
		BOOST_CHECK( state.depth_test == false );
		BOOST_CHECK( state.backface_culling == true );
	}

	// Equality.
	{
		std::shared_ptr<sf::Texture> texture( new sf::Texture );

		{
			sg::RenderState first;
			sg::RenderState second;

			BOOST_CHECK( first == second );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.texture = texture;
			second.texture = texture;
			BOOST_CHECK( first == second );

			second.texture.reset();
			BOOST_CHECK( !(first == second) );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.min_filter = GL_NEAREST_MIPMAP_LINEAR;
			second.min_filter = GL_NEAREST_MIPMAP_LINEAR;
			BOOST_CHECK( first == second );

			second.min_filter = GL_LINEAR;
			BOOST_CHECK( !(first == second) );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.mag_filter = GL_NEAREST_MIPMAP_LINEAR;
			second.mag_filter = GL_NEAREST_MIPMAP_LINEAR;
			BOOST_CHECK( first == second );

			second.mag_filter = GL_LINEAR;
			BOOST_CHECK( !(first == second) );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.wireframe = !first.wireframe;
			second.wireframe = !second.wireframe;
			BOOST_CHECK( first == second );

			second.wireframe = !second.wireframe;
			BOOST_CHECK( !(first == second) );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.depth_test = !first.depth_test;
			second.depth_test = !second.depth_test;
			BOOST_CHECK( first == second );

			second.depth_test = !second.depth_test;
			BOOST_CHECK( !(first == second) );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.backface_culling = !first.backface_culling;
			second.backface_culling = !second.backface_culling;
			BOOST_CHECK( first == second );

			second.backface_culling = !second.backface_culling;
			BOOST_CHECK( !(first == second) );
		}
	}

	// Unequality.
	{
		std::shared_ptr<sf::Texture> texture( new sf::Texture );

		{
			sg::RenderState first;
			sg::RenderState second;

			second.texture = texture;
			BOOST_CHECK( first != second );

			second.texture = first.texture;
			BOOST_CHECK( !(first != second) );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			second.min_filter = GL_NEAREST_MIPMAP_LINEAR;
			BOOST_CHECK( first != second );

			second.min_filter = first.min_filter;
			BOOST_CHECK( !(first != second) );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			second.mag_filter = GL_NEAREST_MIPMAP_LINEAR;
			BOOST_CHECK( first != second );

			second.mag_filter = first.mag_filter;
			BOOST_CHECK( !(first != second) );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			second.wireframe = !first.wireframe;
			BOOST_CHECK( first != second );

			second.wireframe = first.wireframe;
			BOOST_CHECK( !(first != second) );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			second.depth_test = !first.depth_test;
			BOOST_CHECK( first != second );

			second.depth_test = first.depth_test;
			BOOST_CHECK( !(first != second) );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			second.backface_culling = !first.backface_culling;
			BOOST_CHECK( first != second );

			second.backface_culling = first.backface_culling;
			BOOST_CHECK( !(first != second) );
		}
	}

	// Less than.
	{
		std::shared_ptr<sf::Texture> source_texture0( new sf::Texture );
		std::shared_ptr<sf::Texture> source_texture1( new sf::Texture );

		BOOST_REQUIRE( source_texture0.get() != source_texture1.get() );

		std::shared_ptr<sf::Texture> texture0;
		std::shared_ptr<sf::Texture> texture1;

		if( source_texture0.get() < source_texture1.get() ) {
			texture0 = source_texture0;
			texture1 = source_texture1;
		}
		else {
			texture0 = source_texture1;
			texture1 = source_texture0;
		}

		{
			sg::RenderState first;
			sg::RenderState second;

			first.texture = texture0;
			second.texture = texture0;

			BOOST_CHECK( (first < second) == false );
			BOOST_CHECK( (second < first) == false );

			first.texture = texture0;
			second.texture = texture1;

			BOOST_CHECK( (first < second) == true );
			BOOST_CHECK( (second < first) == false );

			first.texture = texture1;
			second.texture = texture0;

			BOOST_CHECK( (first < second) == false );
			BOOST_CHECK( (second < first) == true );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.min_filter = 0;
			first.mag_filter = 0;
			second.min_filter = 1;
			second.mag_filter = 1;
			BOOST_CHECK( (first < second) == true );

			first.min_filter = 1;
			first.mag_filter = 0;
			second.min_filter = 1;
			second.mag_filter = 1;
			BOOST_CHECK( (first < second) == true );

			first.min_filter = 0;
			first.mag_filter = 1;
			second.min_filter = 1;
			second.mag_filter = 1;
			BOOST_CHECK( (first < second) == true );

			first.min_filter = 1;
			first.mag_filter = 1;
			second.min_filter = 1;
			second.mag_filter = 1;
			BOOST_CHECK( (first < second) == false );

			first.min_filter = 2;
			first.mag_filter = 1;
			second.min_filter = 1;
			second.mag_filter = 1;
			BOOST_CHECK( (first < second) == false );

			first.min_filter = 1;
			first.mag_filter = 2;
			second.min_filter = 1;
			second.mag_filter = 1;
			BOOST_CHECK( (first < second) == false );

			first.min_filter = 2;
			first.mag_filter = 2;
			second.min_filter = 1;
			second.mag_filter = 1;
			BOOST_CHECK( (first < second) == false );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.wireframe = false;
			second.wireframe = false;

			BOOST_CHECK( (first < second) == false );
			BOOST_CHECK( (second < first) == false );

			first.wireframe = true;
			second.wireframe = false;

			BOOST_CHECK( (first < second) == true );
			BOOST_CHECK( (second < first) == false );

			first.wireframe = false;
			second.wireframe = true;

			BOOST_CHECK( (first < second) == false );
			BOOST_CHECK( (second < first) == true );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.depth_test = false;
			second.depth_test = false;

			BOOST_CHECK( (first < second) == false );
			BOOST_CHECK( (second < first) == false );

			first.depth_test = true;
			second.depth_test = false;

			BOOST_CHECK( (first < second) == true );
			BOOST_CHECK( (second < first) == false );

			first.depth_test = false;
			second.depth_test = true;

			BOOST_CHECK( (first < second) == false );
			BOOST_CHECK( (second < first) == true );
		}
		{
			sg::RenderState first;
			sg::RenderState second;

			first.backface_culling = false;
			second.backface_culling = false;

			BOOST_CHECK( (first < second) == false );
			BOOST_CHECK( (second < first) == false );

			first.backface_culling = true;
			second.backface_culling = false;

			BOOST_CHECK( (first < second) == true );
			BOOST_CHECK( (second < first) == false );

			first.backface_culling = false;
			second.backface_culling = true;

			BOOST_CHECK( (first < second) == false );
			BOOST_CHECK( (second < first) == true );
		}
	}
}
