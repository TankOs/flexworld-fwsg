#include <GL/glew.h>

#include <FWSG/TriangleGeometry.hpp>
#include <FWSG/Renderer.hpp>
#include <FWSG/Node.hpp>
#include <FWSG/StaticMesh.hpp>
#include <FWSG/WireframeState.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main() {
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Hello World (FWSG example)" );
	sf::Event event;

	// Create a simple geometry object.
	sg::TriangleGeometry geometry;

	geometry.add_triangle(
		sg::Vertex( sf::Vector3f( 0, 0, 0 ) ),
		sg::Vertex( sf::Vector3f( 1, 0, 0 ) ),
		sg::Vertex( sf::Vector3f( 0, 1, 0 ) )
	);

	// Create the buffer object and load the geometry into it.
	sg::BufferObject::Ptr buffer_object( new sg::BufferObject( sg::BufferObject::VERTICES_ONLY, true ) );
	buffer_object->load( geometry );

	// Setup renderer.
	sg::Renderer renderer;

	// Setup the scene graph.
	// Static mesh.
	sg::StaticMesh::Ptr static_mesh = sg::StaticMesh::create( buffer_object, renderer );

	// Same mesh, but in wireframe mode. Also translate it a little bit so it's
	// visible.
	sg::StaticMesh::Ptr wireframe_static_mesh = sg::StaticMesh::create( buffer_object, renderer );
	wireframe_static_mesh->set_state( sg::WireframeState( true ) );
	wireframe_static_mesh->set_local_transform( sg::Transform( sf::Vector3f( -1, 0, 0 ) ) );

	// Create root node and add meshes to it.
	sg::Node::Ptr root_node = sg::Node::create();
	root_node->attach( static_mesh );
	root_node->attach( wireframe_static_mesh );

	// Setup SFML window.
	window.setVerticalSyncEnabled( true );

	// Setup UI.
	sf::Text info_text( L"Press W to toggle wireframe mode for all meshes." );
	info_text.setColor( sf::Color( 0xa2, 0xb4, 0xc6 ) );

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

		// Update scene graph.
		root_node->update();

		// Rendering.
		window.clear();

		// Call renderer and save GL states from being changed by SFML.
		renderer.render();
		window.pushGLStates();

		// Make SFML work again.
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		glDisable( GL_CULL_FACE );
		glDisable( GL_DEPTH_TEST );
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		// Render UI.
		window.draw( info_text );

		// Flip buffers and restore states.
		window.display();
		window.popGLStates();
	}

	return 0;
}
