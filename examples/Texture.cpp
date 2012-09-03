#include <GL/glew.h>

#include <FWSG/TriangleGeometry.hpp>
#include <FWSG/Renderer.hpp>
#include <FWSG/Node.hpp>
#include <FWSG/StaticMesh.hpp>
#include <FWSG/WireframeState.hpp>
#include <FWSG/TextureState.hpp>
#include <FWSG/Camera.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

int main() {
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Texture (FWSG example)" );
	sf::Event event;

	// Create a simple geometry object.
	sg::TriangleGeometry geometry;

	geometry.add_triangle(
		sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector2f( 0, 1 ) ),
		sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector2f( 1, 1 ) ),
		sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ) )
	);
	geometry.add_triangle(
		sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector2f( 1, 1 ) ),
		sg::Vertex( sf::Vector3f( 1, 1, 0 ), sf::Vector2f( 1, 0 ) ),
		sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ) )
	);

	sg::BufferObject::Ptr buffer_object( new sg::BufferObject( sg::BufferObject::TEX_COORDS, true ) );
	buffer_object->load( geometry );

	// Setup renderer.
	sg::Renderer renderer;

	// Prepare textures.
	std::shared_ptr<sf::Texture> nearest_texture( new sf::Texture );
	std::shared_ptr<sf::Texture> linear_texture( new sf::Texture );
	std::shared_ptr<sf::Texture> nearest_mipmap_texture( new sf::Texture );
	std::shared_ptr<sf::Texture> linear_mipmap_texture( new sf::Texture );

	{
		sf::Image image;
		bool color_switch = false;

		image.create( 128, 128 );

		for( sf::Uint32 y = 0; y < image.getSize().y; ++y ) {
			if( y % 16 == 0 ) {
				color_switch = !color_switch;
			}

			for( sf::Uint32 x = 0; x < image.getSize().x; ++x ) {
				if( x % 16 == 0 ) {
					color_switch = !color_switch;
				}

				image.setPixel( x, y, color_switch ? sf::Color::Red : sf::Color::White );
			}
		}

		nearest_texture->loadFromImage( image );
		nearest_texture->bind();
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		linear_texture->loadFromImage( image );
		linear_texture->bind();
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		nearest_mipmap_texture->loadFromImage( image );
		nearest_mipmap_texture->bind();

		gluBuild2DMipmaps(
			GL_TEXTURE_2D,
			GL_RGBA, 
			image.getSize().x,
			image.getSize().y,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image.getPixelsPtr()
		);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

		linear_mipmap_texture->loadFromImage( image );
		linear_mipmap_texture->bind();

		gluBuild2DMipmaps(
			GL_TEXTURE_2D,
			GL_RGBA, 
			image.getSize().x,
			image.getSize().y,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image.getPixelsPtr()
		);

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	}

	// Setup the scene graph.
	// Static meshes.
	sg::StaticMesh::Ptr nearest_mesh = sg::StaticMesh::create( buffer_object, renderer );
	nearest_mesh->set_local_transform( sg::Transform( sf::Vector3f( -0.5f, 0.5f, 0 ), sf::Vector3f( 20, 40, 0 ), sf::Vector3f( 1, 1, 1 ), sf::Vector3f( 0.5f, 0.5f, 0 ) ) );

	sg::StaticMesh::Ptr linear_mesh = sg::StaticMesh::create( buffer_object, renderer );
	linear_mesh->set_local_transform( sg::Transform( sf::Vector3f( 0.5f, 0.5f, 0 ), sf::Vector3f( 20, 40, 0 ), sf::Vector3f( 1, 1, 1 ), sf::Vector3f( 0.5f, 0.5f, 0 ) ) );

	sg::StaticMesh::Ptr nearest_mipmap_mesh = sg::StaticMesh::create( buffer_object, renderer );
	nearest_mipmap_mesh->set_local_transform( sg::Transform( sf::Vector3f( -0.5f, -0.5f, 0 ), sf::Vector3f( 20, 40, 0 ), sf::Vector3f( 1, 1, 1 ), sf::Vector3f( 0.5f, 0.5f, 0 ) ) );

	sg::StaticMesh::Ptr linear_mipmap_mesh = sg::StaticMesh::create( buffer_object, renderer );
	linear_mipmap_mesh->set_local_transform( sg::Transform( sf::Vector3f( 0.5f, -0.5f, 0 ), sf::Vector3f( 20, 40, 0 ), sf::Vector3f( 1, 1, 1 ), sf::Vector3f( 0.5f, 0.5f, 0 ) ) );

	// Create root node and add meshes to it.
	sg::Node::Ptr root_node = sg::Node::create();
	root_node->attach( nearest_mesh );
	root_node->attach( linear_mesh );
	root_node->attach( nearest_mipmap_mesh );
	root_node->attach( linear_mipmap_mesh );

	// Set states.
	nearest_mesh->set_state( sg::TextureState( nearest_texture ) );
	linear_mesh->set_state( sg::TextureState( linear_texture ) );
	nearest_mipmap_mesh->set_state( sg::TextureState( nearest_mipmap_texture ) );
	linear_mipmap_mesh->set_state( sg::TextureState( linear_mipmap_texture ) );

	// Setup camera and viewport.
	sf::FloatRect viewport( 0.0f, 0.0f, 800.0f, 600.0f );
	sg::Camera camera;

	camera.setup_parallel_projection( -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f );

	// Setup SFML window.
	window.setVerticalSyncEnabled( true );

	// Setup UI.
	sf::Font dejavu_font;
	dejavu_font.loadFromFile( "data/DejaVuSans.ttf" );

	sf::Text info_text( L"W: Toggle global wireframe", dejavu_font, 14 );
	info_text.setPosition( 5.0f, static_cast<float>( window.getSize().y ) - info_text.getGlobalBounds().height - 5.0f );
	info_text.setColor( sf::Color( 0, 100, 255 ) );

	sf::Text filter_nearest = info_text;
	filter_nearest.setString( "GL_NEAREST" );
	filter_nearest.setPosition(
		std::floor( static_cast<float>( window.getSize().x ) / 4.0f - filter_nearest.getGlobalBounds().width / 2.0f ),
		std::floor( static_cast<float>( window.getSize().y ) / 4.0f - filter_nearest.getGlobalBounds().height / 2.0f )
	);

	sf::Text filter_linear = info_text;
	filter_linear.setString( "GL_LINEAR" );
	filter_linear.setPosition(
		std::floor( static_cast<float>( window.getSize().x ) / 4.0f * 3.0f - filter_linear.getGlobalBounds().width / 2.0f ),
		std::floor( static_cast<float>( window.getSize().y ) / 4.0f - filter_linear.getGlobalBounds().height / 2.0f )
	);

	sf::Text filter_mipmap_nearest = info_text;
	filter_mipmap_nearest.setString( "GL_NEAREST_MIPMAP_NEAREST" );
	filter_mipmap_nearest.setPosition(
		std::floor( static_cast<float>( window.getSize().x ) / 4.0f - filter_mipmap_nearest.getGlobalBounds().width / 2.0f ),
		std::floor( static_cast<float>( window.getSize().y ) / 4.0f * 3.0f - filter_mipmap_nearest.getGlobalBounds().height / 2.0f )
	);

	sf::Text filter_mipmap_linear = info_text;
	filter_mipmap_linear.setString( "GL_LINEAR_MIPMAP_LINEAR" );
	filter_mipmap_linear.setPosition(
		std::floor( static_cast<float>( window.getSize().x ) / 4.0f * 3.0f - filter_mipmap_linear.getGlobalBounds().width / 2.0f ),
		std::floor( static_cast<float>( window.getSize().y ) / 4.0f * 3.0f - filter_mipmap_linear.getGlobalBounds().height / 2.0f )
	);

	sf::Clock timer;
	float pulse = 0;
	static const float PULSE_INCREMENT = 20.0f;

	while( window.isOpen() ) {
		while( window.pollEvent( event ) ) {
			if( event.type == sf::Event::Closed ) {
				window.close();
			}
			else if( event.type == sf::Event::KeyPressed ) {
				if( event.key.code == sf::Keyboard::Escape ) {
					window.close();
				}
				else if( event.key.code == sf::Keyboard::W ) {
					const sg::WireframeState* wireframe_state = root_node->find_state<sg::WireframeState>();

					root_node->set_state(
						sg::WireframeState(
							(wireframe_state != nullptr) ? !wireframe_state->is_set() : true
						)
					);
				}
			}
		}

		if( timer.getElapsedTime().asSeconds() > 0.001f ) {
			pulse += PULSE_INCREMENT * timer.restart().asSeconds();

			float scale = std::max( 0.01f, std::abs( std::sin( pulse * 3.14159265f / 180.0f ) ) );

			nearest_mesh->set_local_transform(
				sg::Transform(
					nearest_mesh->get_local_transform().get_translation(),
					nearest_mesh->get_local_transform().get_rotation(),
					sf::Vector3f( scale, scale, scale ),
					nearest_mesh->get_local_transform().get_origin()
				)
			);
			linear_mesh->set_local_transform(
				sg::Transform(
					linear_mesh->get_local_transform().get_translation(),
					linear_mesh->get_local_transform().get_rotation(),
					sf::Vector3f( scale, scale, scale ),
					linear_mesh->get_local_transform().get_origin()
				)
			);
			nearest_mipmap_mesh->set_local_transform(
				sg::Transform(
					nearest_mipmap_mesh->get_local_transform().get_translation(),
					nearest_mipmap_mesh->get_local_transform().get_rotation(),
					sf::Vector3f( scale, scale, scale ),
					nearest_mipmap_mesh->get_local_transform().get_origin()
				)
			);
			linear_mipmap_mesh->set_local_transform(
				sg::Transform(
					linear_mipmap_mesh->get_local_transform().get_translation(),
					linear_mipmap_mesh->get_local_transform().get_rotation(),
					sf::Vector3f( scale, scale, scale ),
					linear_mipmap_mesh->get_local_transform().get_origin()
				)
			);
		}

		// Update scene graph.
		root_node->update();

		// Rendering.
		window.clear();

		// Call renderer and save GL states from being changed by SFML.
		renderer.render( camera, viewport );
		window.pushGLStates();

		// Make SFML work again.
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		glDisable( GL_CULL_FACE );
		glDisable( GL_DEPTH_TEST );
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		// Render UI.
		window.draw( info_text );
		window.draw( filter_nearest );
		window.draw( filter_linear );
		window.draw( filter_mipmap_nearest );
		window.draw( filter_mipmap_linear );

		// Flip buffers and restore states.
		window.display();
		window.popGLStates();
	}

	return 0;
}
