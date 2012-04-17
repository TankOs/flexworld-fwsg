#include <GL/glew.h>

#include <FWSG/TriangleGeometry.hpp>
#include <FWSG/Renderer.hpp>
#include <FWSG/Node.hpp>
#include <FWSG/StaticMesh.hpp>
#include <FWSG/Program.hpp>
#include <FWSG/ProgramCommand.hpp>
#include <FWSG/ProgramCommandState.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

int main() {
	sf::RenderWindow window( sf::VideoMode( 800, 600 ), "Shader (FWSG example)" );
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

	sg::BufferObject::Ptr buffer_object( new sg::BufferObject( sg::BufferObject::VERTICES_ONLY, true ) );
	buffer_object->load( geometry );

	// Setup renderer.
	sg::Renderer renderer;

	// Setup the scene graph.
	// Static meshes.
	sg::StaticMesh::Ptr mesh_0 = sg::StaticMesh::create( buffer_object, renderer );
	mesh_0->set_local_transform( sg::Transform( sf::Vector3f( -1, 0, 0 ) ) );

	sg::StaticMesh::Ptr mesh_1 = sg::StaticMesh::create( buffer_object, renderer );
	mesh_1->set_local_transform( sg::Transform( sf::Vector3f( 0, -1, 0 ) ) );

	// Create root node and add meshes to it.
	sg::Node::Ptr root_node = sg::Node::create();
	root_node->attach( mesh_0 );
	root_node->attach( mesh_1 );

	// Create shader program with a simple fragment shader.
	sg::Program::Ptr program( new sg::Program );
	program->add_shader( "uniform vec4 color; void main() { gl_FragColor = color; }", sg::Program::FRAGMENT_SHADER );

	if( !program->link() ) {
		std::cerr << "Failed to link program." << std::endl;
		return EXIT_FAILURE;
	}

	// Register uniforms.
	program->register_uniform( "color" );

	// Create two separate program commands so that we can set different
	// arguments for both meshes.
	sg::ProgramCommand::Ptr command_0( new sg::ProgramCommand( program ) );
	sg::ProgramCommand::Ptr command_1( new sg::ProgramCommand( program ) );

	mesh_0->set_state( sg::ProgramCommandState( command_0 ) );
	mesh_1->set_state( sg::ProgramCommandState( command_1 ) );

	// Set initial values.
	command_0->set_argument( "color", 1.0f, 0.0f, 0.0f, 1.0f );
	command_1->set_argument( "color", 0.0f, 1.0f, 0.0f, 1.0f );

	// Setup SFML window.
	window.setVerticalSyncEnabled( true );

	uint32_t color_mesh_0 = 0xff0000;
	uint32_t color_mesh_1 = 0x00ff00;
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

		// Update scene graph.
		root_node->update();

		if( timer.getElapsedTime().asMilliseconds() >= 50 ) {
			// Update colors.
			color_mesh_0 += 10;
			color_mesh_1 += 10;

			// Update arguments.
			command_0->set_argument(
				"color",
				1.0f,
				static_cast<float>( (color_mesh_0 & 0x00ff00) >>  8 ) / 255.0f,
				static_cast<float>( (color_mesh_0 & 0x0000ff) >>  0 ) / 255.0f,
				0.0f
			);

			command_1->set_argument(
				"color",
				static_cast<float>( (color_mesh_1 & 0xff0000) >> 16 ) / 255.0f,
				1.0f,
				static_cast<float>( (color_mesh_1 & 0x0000ff) >>  0 ) / 255.0f,
				0.0f
			);

			timer.restart();
		}

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

		glDisable( GL_CULL_FACE );
		glDisable( GL_DEPTH_TEST );
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

		// Flip buffers and restore states.
		window.display();
		window.popGLStates();
	}

	return 0;
}
