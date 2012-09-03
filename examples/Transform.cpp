#include <GL/glew.h>

#include <FWSG/TriangleGeometry.hpp>
#include <FWSG/Renderer.hpp>
#include <FWSG/Node.hpp>
#include <FWSG/StaticMesh.hpp>
#include <FWSG/BackfaceCullingState.hpp>
#include <FWSG/Camera.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main() {
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Transform (FWSG example)" );
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
	// Static meshes.
	sg::StaticMesh::Ptr static_mesh0 = sg::StaticMesh::create( buffer_object, renderer );
	sg::StaticMesh::Ptr static_mesh1 = sg::StaticMesh::create( buffer_object, renderer );
	sg::StaticMesh::Ptr static_mesh2 = sg::StaticMesh::create( buffer_object, renderer );

	{
		sg::Transform transform;
		transform.set_origin( sf::Vector3f( 0.5f, 0.5f, 0.0f ) );

		transform.set_translation( sf::Vector3f( 0.5f, 0.5f, 0 ) );
		static_mesh0->set_local_transform( transform );

		transform.set_translation( sf::Vector3f( -0.5f, 0.5f, 0 ) );
		static_mesh1->set_local_transform( transform );

		transform.set_translation( sf::Vector3f( -0.5f, -0.5f, 0 ) );
		static_mesh2->set_local_transform( transform );
	}

	// Create root node and add meshes to it.
	sg::Node::Ptr root_node = sg::Node::create();
	root_node->attach( static_mesh0 );
	root_node->attach( static_mesh1 );
	root_node->attach( static_mesh2 );

	// Disable backface culling to see the back of the meshes.
	root_node->set_state( sg::BackfaceCullingState( false ) );

	// Setup camera and viewport.
	sg::Camera camera( sf::FloatRect( 0.0f, 0.0f, 800.0f, 600.0f ) );

	camera.setup_parallel_projection( -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f );

	// Setup SFML window.
	window.setVerticalSyncEnabled( true );

	// Animation vars.
	static const float ROTATE_SPEED = 90.0f;
	float scale = 1.0f;
	float scale_step = 1.0f;

	sf::Clock timer;

	while( window.isOpen() ) {
		while( window.pollEvent( event ) ) {
			if( event.type == sf::Event::Closed ) {
				window.close();
			}
			else if( event.type == sf::Event::KeyPressed ) {
				if( event.key.code == sf::Keyboard::Escape ) {
					window.close();
				}
			}
		}

		sf::Time frametime = timer.restart();
		float secs = frametime.asSeconds();

		scale += scale_step * secs;

		if( scale > 1.5f ) {
			scale = 1.5f;
			scale_step *= -1.0f;
		}
		else if( scale <= 0.2f ) {
			scale = 0.2f;
			scale_step *= -1.0f;
		}

		// Transform root node.
		root_node->set_local_transform(
			sg::Transform(
				root_node->get_local_transform().get_translation(),
				root_node->get_local_transform().get_rotation(),// + sf::Vector3f( 0, 0, ROTATE_SPEED * secs ),
				root_node->get_local_transform().get_scale(),
				root_node->get_local_transform().get_origin()
			)
		);

		// Transform all 3 meshes.
		static_mesh0->set_local_transform(
			sg::Transform(
				static_mesh0->get_local_transform().get_translation(),
				static_mesh0->get_local_transform().get_rotation() + sf::Vector3f( 0, 0, ROTATE_SPEED * secs ),
				sf::Vector3f( scale, scale, scale ),
				static_mesh0->get_local_transform().get_origin()
			)
		);

		static_mesh1->set_local_transform(
			sg::Transform(
				static_mesh1->get_local_transform().get_translation(),
				static_mesh1->get_local_transform().get_rotation() + sf::Vector3f( 0, ROTATE_SPEED * secs, 0 ),
				sf::Vector3f( scale, scale, scale ),
				static_mesh1->get_local_transform().get_origin()
			)
		);

		static_mesh2->set_local_transform(
			sg::Transform(
				static_mesh2->get_local_transform().get_translation(),
				static_mesh2->get_local_transform().get_rotation() + sf::Vector3f( ROTATE_SPEED * secs, 0, 0 ),
				sf::Vector3f( scale, scale, scale ),
				static_mesh2->get_local_transform().get_origin()
			)
		);

		// Update scene graph.
		root_node->update();

		// Rendering.
		window.clear();

		// Call renderer and save GL states from being changed by SFML.
		renderer.render( camera );
		window.pushGLStates();

		// Make SFML work again.
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_COLOR_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		// Flip buffers and restore states.
		window.display();
		window.popGLStates();
	}

	return 0;
}
