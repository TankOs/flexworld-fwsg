#include <FWSG/Leaf.hpp>
#include <FWSG/Node.hpp>
#include <FWSG/RenderState.hpp>
#include <FWSG/WireframeState.hpp>
#include <FWSG/BackfaceCullingState.hpp>
#include <FWSG/TextureState.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestLeaf ) {
	sf::RenderWindow window( sf::VideoMode( 100, 100 ), "Unittest" );

	// Initial state.
	{
		sg::Leaf::Ptr leaf = sg::Leaf::create();

		BOOST_CHECK( leaf->get_parent() == false );
		BOOST_CHECK( leaf->get_local_transform() == sg::Transform() );
		BOOST_CHECK( leaf->get_global_transform() == sg::Transform() );
		BOOST_CHECK( leaf->is_update_needed() == true );
		BOOST_CHECK( leaf->get_num_states() == 0 );
		BOOST_CHECK( leaf->get_render_state() == sg::RenderState() );
	}

	// Set transform.
	{
		static const sg::Transform TRANSFORM(
			sf::Vector3f( 10, 11, 12 ),
			sf::Vector3f( 20, 21, 22 ),
			sf::Vector3f( 30, 31, 32 )
		);

		sg::Leaf::Ptr leaf = sg::Leaf::create();

		leaf->set_local_transform( TRANSFORM );

		BOOST_CHECK( leaf->get_local_transform() == TRANSFORM );

		// No parent, so global == local.
		BOOST_CHECK( leaf->get_global_transform() == TRANSFORM );
	}

	// Update.
	{
		sg::Leaf::Ptr leaf = sg::Leaf::create();

		BOOST_CHECK( leaf->is_update_needed() == true );
		leaf->update();
		BOOST_CHECK( leaf->is_update_needed() == false );
	}

	// Parent.
	{
		sg::Node::Ptr node = sg::Node::create();
		sg::Leaf::Ptr leaf = sg::Leaf::create();

		leaf->set_parent( node );

		BOOST_CHECK( leaf->get_parent() == node );
		BOOST_CHECK( node->get_num_children() == 0 ); // set_parent won't really add the child to the parent!
	}

	// Queue update.
	{
		sg::Node::Ptr root = sg::Node::create();
		sg::Node::Ptr child = sg::Node::create();
		sg::Leaf::Ptr leaf = sg::Leaf::create();

		root->attach( child );
		child->attach( leaf );

		// Make sure update flag is reset.
		root->update();

		BOOST_CHECK( root->is_update_needed() == false );
		BOOST_CHECK( child->is_update_needed() == false );
		BOOST_CHECK( leaf->is_update_needed() == false );

		// Queue update.
		leaf->queue_update();

		BOOST_CHECK( root->is_update_needed() == true );
		BOOST_CHECK( child->is_update_needed() == true );
		BOOST_CHECK( leaf->is_update_needed() == true );
	}

	std::shared_ptr<sf::Texture> texture( new sf::Texture );

	// States.
	{
		sg::Leaf::Ptr leaf = sg::Leaf::create();

		// Texture.
		BOOST_CHECK( leaf->find_state<sg::TextureState>() == nullptr );

		leaf->set_state( sg::TextureState( texture ) );
		BOOST_CHECK( leaf->find_state<sg::TextureState>() != nullptr );
		BOOST_CHECK( leaf->find_state<sg::TextureState>()->get_texture() == texture );

		{
			sg::RenderState r_state;
			r_state.texture = texture;
			BOOST_CHECK( leaf->get_render_state() == r_state );
		}

		leaf->reset_state<sg::TextureState>();
		BOOST_CHECK( leaf->find_state<sg::TextureState>() == nullptr );

		// Wireframe.
		BOOST_CHECK( leaf->find_state<sg::WireframeState>() == nullptr );

		leaf->set_state( sg::WireframeState( true ) );
		BOOST_CHECK( leaf->find_state<sg::WireframeState>() != nullptr );
		BOOST_CHECK( leaf->find_state<sg::WireframeState>()->is_set() == true );

		{
			sg::RenderState r_state;
			r_state.wireframe = true;
			BOOST_CHECK( leaf->get_render_state() == r_state );
		}

		leaf->set_state( sg::WireframeState( false ) );
		BOOST_CHECK( leaf->find_state<sg::WireframeState>() != nullptr );
		BOOST_CHECK( leaf->find_state<sg::WireframeState>()->is_set() == false );

		// Backface culling.
		BOOST_CHECK( leaf->find_state<sg::BackfaceCullingState>() == nullptr );

		leaf->set_state( sg::BackfaceCullingState( true ) );
		BOOST_CHECK( leaf->find_state<sg::BackfaceCullingState>() != nullptr );
		BOOST_CHECK( leaf->find_state<sg::BackfaceCullingState>()->is_set() == true );

		{
			sg::RenderState r_state;
			r_state.backface_culling = true;
			BOOST_CHECK( leaf->get_render_state() == r_state );
		}

		leaf->set_state( sg::BackfaceCullingState( false ) );
		BOOST_CHECK( leaf->find_state<sg::BackfaceCullingState>() != nullptr );
		BOOST_CHECK( leaf->find_state<sg::BackfaceCullingState>()->is_set() == false );

		{
			sg::RenderState r_state;
			r_state.backface_culling = false;
			BOOST_CHECK( leaf->get_render_state() == r_state );
		}

		leaf->reset_state<sg::WireframeState>();
		BOOST_CHECK( leaf->find_state<sg::WireframeState>() == nullptr );
	}
}
