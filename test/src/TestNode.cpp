#include <FWSG/Node.hpp>
#include <FWSG/RenderState.hpp>
#include <FWSG/WireframeState.hpp>
#include <FWSG/TextureState.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestNode ) {
	sf::RenderWindow window( sf::VideoMode( 100, 100 ), "Unittest" );

	// Initial state.
	{
		sg::Node::Ptr node = sg::Node::create();
		BOOST_CHECK( node->get_num_children() == 0 );

		// Other properties are checked in TestLeaf.
	}

	// Attach.
	{
		sg::Leaf::Ptr leaf0 = sg::Leaf::create();
		sg::Leaf::Ptr leaf1 = sg::Leaf::create();
		sg::Leaf::Ptr leaf2 = sg::Leaf::create();
		sg::Node::Ptr node = sg::Node::create();

		node->attach( leaf0 );
		node->attach( leaf1 );
		node->attach( leaf2 );

		BOOST_CHECK( node->get_num_children() == 3 );
		BOOST_CHECK( node->has_child( leaf0 ) == true );
		BOOST_CHECK( node->has_child( leaf1 ) == true );
		BOOST_CHECK( node->has_child( leaf2 ) == true );

		BOOST_CHECK( leaf0->get_parent() == node );
		BOOST_CHECK( leaf1->get_parent() == node );
		BOOST_CHECK( leaf2->get_parent() == node );
	}

	// Detach.
	{
		sg::Leaf::Ptr leaf = sg::Leaf::create();
		sg::Node::Ptr node = sg::Node::create();

		node->attach( leaf );
		BOOST_CHECK( node->get_num_children() == 1 );
		BOOST_CHECK( leaf->get_parent() == node );

		node->detach( leaf );
		BOOST_CHECK( node->get_num_children() == 0 );
		BOOST_CHECK( leaf->get_parent() == false );
	}

	// Delegation of update call.
	{
		sg::Leaf::Ptr leaf0 = sg::Leaf::create();
		sg::Leaf::Ptr leaf1 = sg::Leaf::create();
		sg::Leaf::Ptr leaf2 = sg::Leaf::create();
		sg::Node::Ptr node = sg::Node::create();

		node->attach( leaf0 );
		node->attach( leaf1 );
		node->attach( leaf2 );

		BOOST_CHECK( node->is_update_needed() == true );
		BOOST_CHECK( leaf0->is_update_needed() == true );
		BOOST_CHECK( leaf1->is_update_needed() == true );
		BOOST_CHECK( leaf2->is_update_needed() == true );

		node->update();

		BOOST_CHECK( node->is_update_needed() == false );
		BOOST_CHECK( leaf0->is_update_needed() == false );
		BOOST_CHECK( leaf1->is_update_needed() == false );
		BOOST_CHECK( leaf2->is_update_needed() == false );
	}

	// Adding a child with queued update queues the update at the parent.
	{
		sg::Node::Ptr root = sg::Node::create();
		sg::Node::Ptr child = sg::Node::create();
		sg::Leaf::Ptr leaf = sg::Leaf::create();

		root->attach( child );
		root->update();

		BOOST_CHECK( root->is_update_needed() == false );
		BOOST_CHECK( child->is_update_needed() == false );
		BOOST_CHECK( leaf->is_update_needed() == true );

		child->attach( leaf );

		BOOST_CHECK( root->is_update_needed() == true );
		BOOST_CHECK( child->is_update_needed() == true );
		BOOST_CHECK( leaf->is_update_needed() == true );
	}

	// Transform delegation/recalculation.
	{
		// Recalculate when calling attach().
		{
			sg::Node::Ptr root = sg::Node::create();
			sg::Node::Ptr child = sg::Node::create();
			sg::Leaf::Ptr leaf = sg::Leaf::create();

			root->set_local_translation( sf::Vector3f( 10, 100, 1000 ) );
			root->set_local_rotation( sf::Vector3f( 11, 110, 1100 ) );
			root->set_scale( sf::Vector3f( 12, 120, 1200 ) );

			child->set_local_translation( sf::Vector3f( 20, 200, 2000 ) );
			child->set_local_rotation( sf::Vector3f( 21, 210, 2100 ) );
			child->set_scale( sf::Vector3f( 22, 220, 2200 ) );

			leaf->set_local_translation( sf::Vector3f( 30, 300, 3000 ) );
			leaf->set_local_rotation( sf::Vector3f( 31, 310, 3100 ) );
			leaf->set_scale( sf::Vector3f( 32, 320, 3200 ) );

			root->attach( child );
			child->attach( leaf );

			BOOST_CHECK( root->get_global_translation() == sf::Vector3f( 10, 100, 1000 ) );
			BOOST_CHECK( root->get_global_rotation() == sf::Vector3f( 11, 110, 1100 ) );
			BOOST_CHECK( root->get_scale() == sf::Vector3f( 12, 120, 1200 ) );

			BOOST_CHECK( child->get_global_translation() == sf::Vector3f( 10 + 20, 100 + 200, 1000 + 2000 ) );
			BOOST_CHECK( child->get_global_rotation() == sf::Vector3f( 11 + 21, 110 + 210, 1100 + 2100 ) );
			BOOST_CHECK( child->get_scale() == sf::Vector3f( 22, 220, 2200 ) );

			BOOST_CHECK( leaf->get_global_translation() == sf::Vector3f( 10 + 20 + 30, 100 + 200 + 300, 1000 + 2000 + 3000 ) );
			BOOST_CHECK( leaf->get_global_rotation() == sf::Vector3f( 11 + 21 + 31, 110 + 210 + 310, 1100 + 2100 + 3100 ) );
			BOOST_CHECK( leaf->get_scale() == sf::Vector3f( 32, 320, 3200 ) );
		}

		// Same, but other ordering.
		{
			sg::Node::Ptr root = sg::Node::create();
			sg::Node::Ptr child = sg::Node::create();
			sg::Leaf::Ptr leaf = sg::Leaf::create();

			root->set_local_translation( sf::Vector3f( 10, 100, 1000 ) );
			root->set_local_rotation( sf::Vector3f( 11, 110, 1100 ) );
			root->set_scale( sf::Vector3f( 12, 120, 1200 ) );

			child->set_local_translation( sf::Vector3f( 20, 200, 2000 ) );
			child->set_local_rotation( sf::Vector3f( 21, 210, 2100 ) );
			child->set_scale( sf::Vector3f( 22, 220, 2200 ) );

			leaf->set_local_translation( sf::Vector3f( 30, 300, 3000 ) );
			leaf->set_local_rotation( sf::Vector3f( 31, 310, 3100 ) );
			leaf->set_scale( sf::Vector3f( 32, 320, 3200 ) );

			child->attach( leaf );
			root->attach( child );

			BOOST_CHECK( root->get_global_translation() == sf::Vector3f( 10, 100, 1000 ) );
			BOOST_CHECK( root->get_global_rotation() == sf::Vector3f( 11, 110, 1100 ) );
			BOOST_CHECK( root->get_scale() == sf::Vector3f( 12, 120, 1200 ) );

			BOOST_CHECK( child->get_global_translation() == sf::Vector3f( 10 + 20, 100 + 200, 1000 + 2000 ) );
			BOOST_CHECK( child->get_global_rotation() == sf::Vector3f( 11 + 21, 110 + 210, 1100 + 2100 ) );
			BOOST_CHECK( child->get_scale() == sf::Vector3f( 22, 220, 2200 ) );

			BOOST_CHECK( leaf->get_global_translation() == sf::Vector3f( 10 + 20 + 30, 100 + 200 + 300, 1000 + 2000 + 3000 ) );
			BOOST_CHECK( leaf->get_global_rotation() == sf::Vector3f( 11 + 21 + 31, 110 + 210 + 310, 1100 + 2100 + 3100 ) );
			BOOST_CHECK( leaf->get_scale() == sf::Vector3f( 32, 320, 3200 ) );
		}

		// Update transformation after adding childs.
		{
			sg::Node::Ptr root = sg::Node::create();
			sg::Node::Ptr child = sg::Node::create();
			sg::Leaf::Ptr leaf = sg::Leaf::create();

			child->attach( leaf );
			root->attach( child );

			root->set_local_translation( sf::Vector3f( 10, 100, 1000 ) );
			root->set_local_rotation( sf::Vector3f( 11, 110, 1100 ) );
			root->set_scale( sf::Vector3f( 12, 120, 1200 ) );

			child->set_local_translation( sf::Vector3f( 20, 200, 2000 ) );
			child->set_local_rotation( sf::Vector3f( 21, 210, 2100 ) );
			child->set_scale( sf::Vector3f( 22, 220, 2200 ) );

			leaf->set_local_translation( sf::Vector3f( 30, 300, 3000 ) );
			leaf->set_local_rotation( sf::Vector3f( 31, 310, 3100 ) );
			leaf->set_scale( sf::Vector3f( 32, 320, 3200 ) );

			BOOST_CHECK( root->get_global_translation() == sf::Vector3f( 10, 100, 1000 ) );
			BOOST_CHECK( root->get_global_rotation() == sf::Vector3f( 11, 110, 1100 ) );
			BOOST_CHECK( root->get_scale() == sf::Vector3f( 12, 120, 1200 ) );

			BOOST_CHECK( child->get_global_translation() == sf::Vector3f( 10 + 20, 100 + 200, 1000 + 2000 ) );
			BOOST_CHECK( child->get_global_rotation() == sf::Vector3f( 11 + 21, 110 + 210, 1100 + 2100 ) );
			BOOST_CHECK( child->get_scale() == sf::Vector3f( 22, 220, 2200 ) );

			BOOST_CHECK( leaf->get_global_translation() == sf::Vector3f( 10 + 20 + 30, 100 + 200 + 300, 1000 + 2000 + 3000 ) );
			BOOST_CHECK( leaf->get_global_rotation() == sf::Vector3f( 11 + 21 + 31, 110 + 210 + 310, 1100 + 2100 + 3100 ) );
			BOOST_CHECK( leaf->get_scale() == sf::Vector3f( 32, 320, 3200 ) );
		}
	}

	std::shared_ptr<sf::Texture> texture( new sf::Texture );

	// Inherit states.
	{
		sg::Node::Ptr root = sg::Node::create();
		sg::Node::Ptr child = sg::Node::create();
		sg::Leaf::Ptr leaf = sg::Leaf::create();

		root->set_state( sg::TextureState( texture ) );
		child->set_state( sg::WireframeState( true ) );
		leaf->set_state( sg::WireframeState( false ) );

		child->attach( leaf );
		root->attach( child );

		// Check root.
		{
			sg::RenderState r_state;
			r_state.texture = texture;

			BOOST_CHECK( root->get_render_state() == r_state );
		}

		// Check child.
		{
			sg::RenderState r_state;
			r_state.texture = texture;
			r_state.wireframe = true;

			BOOST_CHECK( child->get_render_state() == r_state );
		}

		// Check leaf.
		{
			sg::RenderState r_state;
			r_state.texture = texture;
			r_state.wireframe = false;

			BOOST_CHECK( leaf->get_render_state() == r_state );
		}
	}
}
