#include <GL/glew.h>

#include <FWSG/Renderer.hpp>
#include <FWSG/Node.hpp>
#include <FWSG/StaticMesh.hpp>
#include <FWSG/WireframeState.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main() {
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Hello World (FWSG example)" );
	sf::Event event;

	// Create a simple triangle mesh.
	sg::BufferObject::Ptr mesh( new sg::BufferObject( sg::BufferObject::VERTICES_ONLY ) );
	mesh->add_vertex( sg::Vertex( sf::Vector3f( 0, 0, 0 ) ) );
	mesh->add_vertex( sg::Vertex( sf::Vector3f( 1, 0, 0 ) ) );
	mesh->add_vertex( sg::Vertex( sf::Vector3f( 0, 1, 0 ) ) );

	// Setup renderer.
	sg::Renderer renderer;

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
	root_node->add_child( mesh_leaf );
	root_node->add_child( wireframe_mesh_leaf );

	// Setup SFML window.
	window.EnableVerticalSync( true );

	// Setup UI.
	sf::Text info_text( L"Press W to toggle wireframe mode for all meshes." );
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
