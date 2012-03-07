#include <GL/glew.h>

#include <FWSG/TriangleGeometry.hpp>
#include <FWSG/Renderer.hpp>
#include <FWSG/Node.hpp>
#include <FWSG/StaticMesh.hpp>
#include <FWSG/BackfaceCullingState.hpp>

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

	static_mesh1->set_local_transform( sg::Transform( sf::Vector3f( -1, 0, 0 ) ) );
	static_mesh2->set_local_transform( sg::Transform( sf::Vector3f( -1, -1, 0 ) ) );

	// Create root node and add meshes to it.
	sg::Node::Ptr root_node = sg::Node::create();
	root_node->attach( static_mesh0 );
	root_node->attach( static_mesh1 );
	root_node->attach( static_mesh2 );

	// Disable backface culling to see the back of the meshes.
	root_node->set_state( sg::BackfaceCullingState( false ) );

	// Setup SFML window.
	window.EnableVerticalSync( true );

	while( window.IsOpen() ) {
		while( window.PollEvent( event ) ) {
			if( event.Type == sf::Event::Closed ) {
				window.Close();
			}
			else if( event.Type == sf::Event::KeyPressed ) {
				if( event.Key.Code == sf::Keyboard::Escape ) {
					window.Close();
				}
			}
		}

		// Rotate all 3 meshes.
		static_mesh0->set_local_transform(
			sg::Transform(
				static_mesh0->get_local_transform().get_translation(),
				static_mesh0->get_local_transform().get_rotation() + sf::Vector3f( 0, 0, 1 ),
				static_mesh0->get_local_transform().get_scale()
			)
		);

		static_mesh1->set_local_transform(
			sg::Transform(
				static_mesh1->get_local_transform().get_translation(),
				static_mesh1->get_local_transform().get_rotation() + sf::Vector3f( 0, 1, 0 ),
				static_mesh1->get_local_transform().get_scale()
			)
		);

		static_mesh2->set_local_transform(
			sg::Transform(
				static_mesh2->get_local_transform().get_translation(),
				static_mesh2->get_local_transform().get_rotation() + sf::Vector3f( 1, 0, 0 ),
				static_mesh2->get_local_transform().get_scale()
			)
		);

		// Update scene graph.
		root_node->update();

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
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		// Flip buffers and restore states.
		window.Display();
		window.PopGLStates();
	}

	return 0;
}
