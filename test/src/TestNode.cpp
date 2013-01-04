#include "Window.hpp"

#include <FWSG/Node.hpp>
#include <FWSG/RenderState.hpp>
#include <FWSG/WireframeState.hpp>
#include <FWSG/TextureState.hpp>
#include <FWSG/BackfaceCullingState.hpp>
#include <FWSG/DepthTestState.hpp>
#include <FWSG/ProgramCommandState.hpp>
#include <FWSG/Program.hpp>
#include <FWSG/ProgramCommand.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestNode ) {
	init_test_window();

	// Initial state.
	{
		sg::Node::Ptr node = sg::Node::create();

		BOOST_CHECK( node->get_num_children() == 0 );
		BOOST_CHECK( node->get_parent() == false );
		BOOST_CHECK( node->get_local_transform() == sg::Transform() );
		BOOST_CHECK( node->get_global_matrix() == util::FloatMatrix() );
		BOOST_CHECK( node->is_update_needed() == true );
		BOOST_CHECK( node->get_num_states() == 0 );
		BOOST_CHECK( node->get_render_state() == sg::RenderState() );
	}

	// Set transform.
	{
		static const sg::Transform TRANSFORM(
			sf::Vector3f( 10, 11, 12 ),
			sf::Vector3f( 20, 21, 22 ),
			sf::Vector3f( 30, 31, 32 ),
			sf::Vector3f( 40, 41, 42 )
		);

		sg::Node::Ptr node = sg::Node::create();

		node->set_local_transform( TRANSFORM );

		BOOST_CHECK( node->get_local_transform() == TRANSFORM );

		// No parent, so global == local.
		BOOST_CHECK( node->get_global_matrix() == TRANSFORM.get_matrix() );
	}

	// Update.
	{
		sg::Node::Ptr node = sg::Node::create();

		BOOST_CHECK( node->is_update_needed() == true );
		node->update();
		BOOST_CHECK( node->is_update_needed() == false );
	}

	// Parent.
	{
		sg::Node::Ptr node = sg::Node::create();
		sg::Node::Ptr child = sg::Node::create();

		child->set_parent( node );

		BOOST_CHECK( child->get_parent() == node );
		BOOST_CHECK( node->get_num_children() == 0 ); // set_parent won't really add the child to the parent!
	}

	// Queue update.
	{
		sg::Node::Ptr root = sg::Node::create();
		sg::Node::Ptr child = sg::Node::create();
		sg::Node::Ptr grandchild = sg::Node::create();

		root->attach( child );
		child->attach( grandchild );

		// Make sure update flag is reset.
		root->update();

		BOOST_CHECK( root->is_update_needed() == false );
		BOOST_CHECK( child->is_update_needed() == false );
		BOOST_CHECK( grandchild->is_update_needed() == false );

		// Queue update.
		grandchild->queue_update();

		BOOST_CHECK( root->is_update_needed() == true );
		BOOST_CHECK( child->is_update_needed() == true );
		BOOST_CHECK( grandchild->is_update_needed() == true );
	}

	std::shared_ptr<sf::Texture> texture( new sf::Texture );

	// Create test program.
	sg::Program::Ptr program( new sg::Program );
	BOOST_REQUIRE( program->add_shader( "void main() { gl_FragColor = vec4( 1, 1, 1, 1 ); }", sg::Program::FRAGMENT_SHADER ) );
	BOOST_REQUIRE( program->link() );

	sg::ProgramCommand::Ptr program_command( new sg::ProgramCommand( program ) );

	// States.
	{
		sg::Node::Ptr node = sg::Node::create();

		// Program command.
		BOOST_CHECK( node->find_state<sg::ProgramCommandState>() == nullptr );

		node->set_state( sg::ProgramCommandState( program_command ) );
		BOOST_CHECK( node->find_state<sg::ProgramCommandState>() != nullptr );
		BOOST_CHECK( node->find_state<sg::ProgramCommandState>()->get_program_command() == program_command );

		node->reset_state<sg::ProgramCommandState>();
		BOOST_CHECK( node->find_state<sg::ProgramCommandState>() == nullptr );

		// Texture.
		BOOST_CHECK( node->find_state<sg::TextureState>() == nullptr );

		node->set_state( sg::TextureState( texture ) );
		BOOST_CHECK( node->find_state<sg::TextureState>() != nullptr );
		BOOST_CHECK( node->find_state<sg::TextureState>()->get_texture() == texture );

		{
			sg::RenderState r_state;
			r_state.texture = texture;
			BOOST_CHECK( node->get_render_state() == r_state );
		}

		node->reset_state<sg::TextureState>();
		BOOST_CHECK( node->find_state<sg::TextureState>() == nullptr );

		// Wireframe.
		BOOST_CHECK( node->find_state<sg::WireframeState>() == nullptr );

		node->set_state( sg::WireframeState( true ) );
		BOOST_CHECK( node->find_state<sg::WireframeState>() != nullptr );
		BOOST_CHECK( node->find_state<sg::WireframeState>()->is_set() == true );

		{
			sg::RenderState r_state;
			r_state.wireframe = true;
			BOOST_CHECK( node->get_render_state() == r_state );
		}

		node->set_state( sg::WireframeState( false ) );
		BOOST_CHECK( node->find_state<sg::WireframeState>() != nullptr );
		BOOST_CHECK( node->find_state<sg::WireframeState>()->is_set() == false );

		node->reset_state<sg::WireframeState>();
		BOOST_CHECK( node->find_state<sg::WireframeState>() == nullptr );

		// Backface culling.
		BOOST_CHECK( node->find_state<sg::BackfaceCullingState>() == nullptr );

		node->set_state( sg::BackfaceCullingState( true ) );
		BOOST_CHECK( node->find_state<sg::BackfaceCullingState>() != nullptr );
		BOOST_CHECK( node->find_state<sg::BackfaceCullingState>()->is_set() == true );

		{
			sg::RenderState r_state;
			r_state.backface_culling = true;
			BOOST_CHECK( node->get_render_state() == r_state );
		}

		node->set_state( sg::BackfaceCullingState( false ) );
		BOOST_CHECK( node->find_state<sg::BackfaceCullingState>() != nullptr );
		BOOST_CHECK( node->find_state<sg::BackfaceCullingState>()->is_set() == false );

		{
			sg::RenderState r_state;
			r_state.backface_culling = false;
			BOOST_CHECK( node->get_render_state() == r_state );
		}

		node->reset_state<sg::BackfaceCullingState>();
		BOOST_CHECK( node->find_state<sg::BackfaceCullingState>() == nullptr );

		// Depth test.
		BOOST_CHECK( node->find_state<sg::DepthTestState>() == nullptr );

		node->set_state( sg::DepthTestState( true ) );
		BOOST_CHECK( node->find_state<sg::DepthTestState>() != nullptr );
		BOOST_CHECK( node->find_state<sg::DepthTestState>()->is_set() == true );

		{
			sg::RenderState r_state;
			r_state.depth_test = true;
			BOOST_CHECK( node->get_render_state() == r_state );
		}

		node->set_state( sg::DepthTestState( false ) );
		BOOST_CHECK( node->find_state<sg::DepthTestState>() != nullptr );
		BOOST_CHECK( node->find_state<sg::DepthTestState>()->is_set() == false );

		{
			sg::RenderState r_state;
			r_state.depth_test = false;
			BOOST_CHECK( node->get_render_state() == r_state );
		}
	}

	// Attach.
	{
		sg::Node::Ptr child0 = sg::Node::create();
		sg::Node::Ptr child1 = sg::Node::create();
		sg::Node::Ptr child2 = sg::Node::create();
		sg::Node::Ptr node = sg::Node::create();

		node->attach( child0 );
		node->attach( child1 );
		node->attach( child2 );

		BOOST_CHECK( node->get_num_children() == 3 );
		BOOST_CHECK( node->has_child( child0 ) == true );
		BOOST_CHECK( node->has_child( child1 ) == true );
		BOOST_CHECK( node->has_child( child2 ) == true );

		BOOST_CHECK( child0->get_parent() == node );
		BOOST_CHECK( child1->get_parent() == node );
		BOOST_CHECK( child2->get_parent() == node );
	}

	// Detach.
	{
		sg::Node::Ptr child = sg::Node::create();
		sg::Node::Ptr node = sg::Node::create();

		node->attach( child );
		BOOST_CHECK( node->get_num_children() == 1 );
		BOOST_CHECK( child->get_parent() == node );

		node->detach( child );
		BOOST_CHECK( node->get_num_children() == 0 );
		BOOST_CHECK( child->get_parent() == false );
	}

	// Delegation of update call.
	{
		sg::Node::Ptr child0 = sg::Node::create();
		sg::Node::Ptr child1 = sg::Node::create();
		sg::Node::Ptr child2 = sg::Node::create();
		sg::Node::Ptr node = sg::Node::create();

		node->attach( child0 );
		node->attach( child1 );
		node->attach( child2 );

		BOOST_CHECK( node->is_update_needed() == true );
		BOOST_CHECK( child0->is_update_needed() == true );
		BOOST_CHECK( child1->is_update_needed() == true );
		BOOST_CHECK( child2->is_update_needed() == true );

		node->update();

		BOOST_CHECK( node->is_update_needed() == false );
		BOOST_CHECK( child0->is_update_needed() == false );
		BOOST_CHECK( child1->is_update_needed() == false );
		BOOST_CHECK( child2->is_update_needed() == false );
	}

	// Adding a child with queued update queues the update at the parent.
	{
		sg::Node::Ptr root = sg::Node::create();
		sg::Node::Ptr child = sg::Node::create();
		sg::Node::Ptr grandchild = sg::Node::create();

		root->attach( child );
		root->update();

		BOOST_CHECK( root->is_update_needed() == false );
		BOOST_CHECK( child->is_update_needed() == false );
		BOOST_CHECK( grandchild->is_update_needed() == true );

		child->attach( grandchild );

		BOOST_CHECK( root->is_update_needed() == true );
		BOOST_CHECK( child->is_update_needed() == true );
		BOOST_CHECK( grandchild->is_update_needed() == true );
	}

	// Transform delegation/recalculation.
	{
		static const sg::Transform ROOT_TRANSFORM(
			sf::Vector3f( 10, 100, 1000 ),
			sf::Vector3f( 11, 110, 1100 ),
			sf::Vector3f( 12, 120, 1200 ),
			sf::Vector3f( 13, 130, 1300 )
		);
		static const sg::Transform CHILD_TRANSFORM(
			sf::Vector3f( 20, 200, 2000 ),
			sf::Vector3f( 21, 210, 2100 ),
			sf::Vector3f( 22, 220, 2200 ),
			sf::Vector3f( 23, 230, 2300 )
		);
		static const sg::Transform LEAF_TRANSFORM(
			sf::Vector3f( 30, 300, 3000 ),
			sf::Vector3f( 31, 310, 3100 ),
			sf::Vector3f( 32, 320, 3200 ),
			sf::Vector3f( 33, 330, 3300 )
		);

		util::FloatMatrix GLOBAL_ROOT_MATRIX = ROOT_TRANSFORM.get_matrix();

		util::FloatMatrix GLOBAL_CHILD_MATRIX = GLOBAL_ROOT_MATRIX;
		GLOBAL_CHILD_MATRIX.multiply( CHILD_TRANSFORM.get_matrix() );

		util::FloatMatrix GLOBAL_LEAF_MATRIX = GLOBAL_CHILD_MATRIX;
		GLOBAL_LEAF_MATRIX.multiply( LEAF_TRANSFORM.get_matrix() );

		// Recalculate when calling attach().
		{
			sg::Node::Ptr root = sg::Node::create();
			sg::Node::Ptr child = sg::Node::create();
			sg::Node::Ptr grandchild = sg::Node::create();

			root->set_local_transform( ROOT_TRANSFORM );
			child->set_local_transform( CHILD_TRANSFORM );
			grandchild->set_local_transform( LEAF_TRANSFORM );

			root->attach( child );
			child->attach( grandchild );

			BOOST_CHECK( root->get_global_matrix() == GLOBAL_ROOT_MATRIX );
			BOOST_CHECK( child->get_global_matrix() == GLOBAL_CHILD_MATRIX );
			BOOST_CHECK( grandchild->get_global_matrix() == GLOBAL_LEAF_MATRIX );
		}

		// Same, but other ordering.
		{
			sg::Node::Ptr root = sg::Node::create();
			sg::Node::Ptr child = sg::Node::create();
			sg::Node::Ptr grandchild = sg::Node::create();

			root->set_local_transform( ROOT_TRANSFORM );
			child->set_local_transform( CHILD_TRANSFORM );
			grandchild->set_local_transform( LEAF_TRANSFORM );

			child->attach( grandchild );
			root->attach( child );

			BOOST_CHECK( root->get_global_matrix() == GLOBAL_ROOT_MATRIX );
			BOOST_CHECK( child->get_global_matrix() == GLOBAL_CHILD_MATRIX );
			BOOST_CHECK( grandchild->get_global_matrix() == GLOBAL_LEAF_MATRIX );
		}

		// Update transformation after adding childs.
		{
			sg::Node::Ptr root = sg::Node::create();
			sg::Node::Ptr child = sg::Node::create();
			sg::Node::Ptr grandchild = sg::Node::create();

			child->attach( grandchild );
			root->attach( child );

			root->set_local_transform( ROOT_TRANSFORM );
			child->set_local_transform( CHILD_TRANSFORM );
			grandchild->set_local_transform( LEAF_TRANSFORM );

			BOOST_CHECK( root->get_global_matrix() == GLOBAL_ROOT_MATRIX );
			BOOST_CHECK( child->get_global_matrix() == GLOBAL_CHILD_MATRIX );
			BOOST_CHECK( grandchild->get_global_matrix() == GLOBAL_LEAF_MATRIX );
		}
	}

	std::shared_ptr<sf::Texture> texture2( new sf::Texture );

	// Create test programs.
	sg::Program::Ptr program_0( new sg::Program );
	BOOST_REQUIRE( program_0->add_shader( "void main() { gl_FragColor = vec4( 1, 1, 1, 1 ); }", sg::Program::FRAGMENT_SHADER ) );
	BOOST_REQUIRE( program_0->link() );

	sg::Program::Ptr program_1( new sg::Program );
	BOOST_REQUIRE( program_1->add_shader( "void main() { gl_FragColor = vec4( 1, 1, 1, 1 ); }", sg::Program::FRAGMENT_SHADER ) );
	BOOST_REQUIRE( program_1->link() );

	// Create test program command.
	sg::ProgramCommand::Ptr program_command_0( new sg::ProgramCommand( program_0 ) );
	sg::ProgramCommand::Ptr program_command_1( new sg::ProgramCommand( program_1 ) );


	// Inherit states.
	{
		sg::Node::Ptr root = sg::Node::create();
		sg::Node::Ptr child = sg::Node::create();
		sg::Node::Ptr grandchild = sg::Node::create();

		root->set_state( sg::ProgramCommandState( program_command_0 ) );
		root->set_state( sg::TextureState( texture ) );
		root->set_state( sg::WireframeState( false ) );
		root->set_state( sg::DepthTestState( false ) );
		root->set_state( sg::BackfaceCullingState( false ) );
		child->set_state( sg::ProgramCommandState( program_command_1 ) );
		child->set_state( sg::TextureState( texture2 ) );
		child->set_state( sg::WireframeState( true ) );
		child->set_state( sg::DepthTestState( true ) );
		child->set_state( sg::BackfaceCullingState( true ) );

		child->attach( grandchild );
		root->attach( child );

		// Check root.
		{
			sg::RenderState r_state;
			r_state.program_command = program_command_0;
			r_state.texture = texture;
			r_state.wireframe = false;
			r_state.depth_test = false;
			r_state.backface_culling = false;

			BOOST_CHECK( root->get_render_state() == r_state );
		}

		// Check child + grandchild.
		{
			sg::RenderState r_state;
			r_state.program_command = program_command_1;
			r_state.texture = texture2;
			r_state.wireframe = true;
			r_state.depth_test = true;
			r_state.backface_culling = true;

			BOOST_CHECK( child->get_render_state() == r_state );
			BOOST_CHECK( grandchild->get_render_state() == r_state );
		}
	}
}
