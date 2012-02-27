#include <GL/glew.h>

#include <FWSG/Renderer.hpp>
#include <FWSG/Node.hpp>
#include <FWSG/StaticMesh.hpp>
#include <FWSG/WireframeState.hpp>
#include <FWSG/TextureState.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

int main() {
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Texture (FWSG example)" );
	sf::Event event;

	// Create a simple quad mesh.
	sg::BufferObject::Ptr mesh( new sg::BufferObject( sg::BufferObject::TEX_COORDS ) );
	mesh->add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 0 ), sf::Vector2f( 0, 1 ) ) );
	mesh->add_vertex( sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector2f( 1, 1 ) ) );
	mesh->add_vertex( sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ) ) );
	mesh->add_vertex( sg::Vertex( sf::Vector3f( 1, 0, 0 ), sf::Vector2f( 1, 1 ) ) );
	mesh->add_vertex( sg::Vertex( sf::Vector3f( 1, 1, 0 ), sf::Vector2f( 1, 0 ) ) );
	mesh->add_vertex( sg::Vertex( sf::Vector3f( 0, 1, 0 ), sf::Vector2f( 0, 0 ) ) );

	// Setup renderer.
	sg::Renderer renderer;

	// Prepare texture.
	std::shared_ptr<sf::Texture> texture( new sf::Texture );

	{
		sf::Image image;
		bool color_switch = false;

		image.Create( 128, 128 );

		for( sf::Uint32 y = 0; y < image.GetHeight(); ++y ) {
			for( sf::Uint32 x = 0; x < image.GetWidth(); ++x ) {
				image.SetPixel( x, y, color_switch ? sf::Color::Red : sf::Color::White );
			}

			if( y % 32 == 0 ) {
				color_switch = !color_switch;
			}
		}

		texture->LoadFromImage( image );
	}


	// Setup the scene graph.
	// Static mesh.
	sg::StaticMesh::Ptr mesh_leaf = sg::StaticMesh::create( mesh, renderer );

	// Same mesh, but in wireframe mode. Also translate it a little bit so it's
	// visible.
	sg::StaticMesh::Ptr wireframe_mesh_leaf = sg::StaticMesh::create( mesh, renderer );
	wireframe_mesh_leaf->set_state( sg::WireframeState( true ) );
	wireframe_mesh_leaf->set_local_translation( sf::Vector3f( -1, 0, 0 ) );

	// Create root node and add meshes to it.
	sg::Node::Ptr root_node = sg::Node::create();
	root_node->attach( mesh_leaf );
	root_node->attach( wireframe_mesh_leaf );
	root_node->set_state( sg::TextureState( texture ) );

	// Setup SFML window.
	window.EnableVerticalSync( true );

	// Setup UI.
	sf::Text info_text( L"W: Toggle global wireframe / T: Toggle global texturing" );
	info_text.SetColor( sf::Color( 0xa2, 0xb4, 0xc6 ) );

	while( window.IsOpen() ) {
		while( window.PollEvent( event ) ) {
			if( event.Type == sf::Event::Closed ) {
				window.Close();
			}
			else if( event.Type == sf::Event::KeyPressed ) {
				if( event.Key.Code == sf::Keyboard::Escape ) {
					window.Close();
				}
				else if( event.Key.Code == sf::Keyboard::W ) {
					const sg::WireframeState* wireframe_state = root_node->find_state<sg::WireframeState>();

					root_node->set_state(
						sg::WireframeState(
							(wireframe_state != nullptr) ? !wireframe_state->is_set() : true
						)
					);
				}
				else if( event.Key.Code == sf::Keyboard::T ) {
					if( root_node->find_state<sg::TextureState>() != nullptr ) {
						root_node->reset_state<sg::TextureState>();
					}
					else {
						root_node->set_state( sg::TextureState( texture ) );
					}
				}
			}
		}

		// Update scene graph and renderer.
		root_node->update();
		renderer.update();

		// Rendering.
		window.Clear();

		// Call renderer and save GL states from being changed by SFML.
		renderer.render();
		window.PushGLStates();

		// Make SFML work again.
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		// Render UI.
		window.Draw( info_text );

		// Flip buffers and restore states.
		window.Display();
		window.PopGLStates();
	}

	return 0;
}
