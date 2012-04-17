#include "Window.hpp"

#include <FWSG/Node.hpp>
#include <FWSG/RenderState.hpp>
#include <FWSG/WireframeState.hpp>
#include <FWSG/TextureState.hpp>
#include <FWSG/BackfaceCullingState.hpp>
#include <FWSG/DepthTestState.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestNode ) {
	init_test_window();

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

		static const sg::Transform GLOBAL_ROOT_TRANSFORM = sg::Transform();
		static const sg::Transform GLOBAL_CHILD_TRANSFORM = ROOT_TRANSFORM;
		static const sg::Transform GLOBAL_LEAF_TRANSFORM(
			ROOT_TRANSFORM.get_translation() + CHILD_TRANSFORM.get_translation(),
			ROOT_TRANSFORM.get_rotation() + CHILD_TRANSFORM.get_rotation(),
			sf::Vector3f(
				ROOT_TRANSFORM.get_scale().x * CHILD_TRANSFORM.get_scale().x,
				ROOT_TRANSFORM.get_scale().y * CHILD_TRANSFORM.get_scale().y,
				ROOT_TRANSFORM.get_scale().z * CHILD_TRANSFORM.get_scale().z
			),
			ROOT_TRANSFORM.get_origin() + CHILD_TRANSFORM.get_origin()
		);

		// Recalculate when calling attach().
		{
			sg::Node::Ptr root = sg::Node::create();
			sg::Node::Ptr child = sg::Node::create();
			sg::Leaf::Ptr leaf = sg::Leaf::create();

			root->set_local_transform( ROOT_TRANSFORM );
			child->set_local_transform( CHILD_TRANSFORM );
			leaf->set_local_transform( LEAF_TRANSFORM );

			root->attach( child );
			child->attach( leaf );

			BOOST_CHECK( root->get_global_transform() == GLOBAL_ROOT_TRANSFORM );
			BOOST_CHECK( child->get_global_transform() == GLOBAL_CHILD_TRANSFORM );
			BOOST_CHECK( leaf->get_global_transform() == GLOBAL_LEAF_TRANSFORM );
		}

		// Same, but other ordering.
		{
			sg::Node::Ptr root = sg::Node::create();
			sg::Node::Ptr child = sg::Node::create();
			sg::Leaf::Ptr leaf = sg::Leaf::create();

			root->set_local_transform( ROOT_TRANSFORM );
			child->set_local_transform( CHILD_TRANSFORM );
			leaf->set_local_transform( LEAF_TRANSFORM );

			child->attach( leaf );
			root->attach( child );

			BOOST_CHECK( root->get_global_transform() == GLOBAL_ROOT_TRANSFORM );
			BOOST_CHECK( child->get_global_transform() == GLOBAL_CHILD_TRANSFORM );
			BOOST_CHECK( leaf->get_global_transform() == GLOBAL_LEAF_TRANSFORM );
		}

		// Update transformation after adding childs.
		{
			sg::Node::Ptr root = sg::Node::create();
			sg::Node::Ptr child = sg::Node::create();
			sg::Leaf::Ptr leaf = sg::Leaf::create();

			child->attach( leaf );
			root->attach( child );

			root->set_local_transform( ROOT_TRANSFORM );
			child->set_local_transform( CHILD_TRANSFORM );
			leaf->set_local_transform( LEAF_TRANSFORM );

			BOOST_CHECK( root->get_global_transform() == GLOBAL_ROOT_TRANSFORM );
			BOOST_CHECK( child->get_global_transform() == GLOBAL_CHILD_TRANSFORM );
			BOOST_CHECK( leaf->get_global_transform() == GLOBAL_LEAF_TRANSFORM );
		}
	}

	std::shared_ptr<sf::Texture> texture( new sf::Texture );
	std::shared_ptr<sf::Texture> texture2( new sf::Texture );

	// Inherit states.
	{
		sg::Node::Ptr root = sg::Node::create();
		sg::Node::Ptr child = sg::Node::create();
		sg::Leaf::Ptr leaf = sg::Leaf::create();

		root->set_state( sg::TextureState( texture, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR ) );
		root->set_state( sg::WireframeState( false ) );
		root->set_state( sg::DepthTestState( false ) );
		root->set_state( sg::BackfaceCullingState( false ) );
		child->set_state( sg::TextureState( texture2, GL_NEAREST, GL_LINEAR ) );
		child->set_state( sg::WireframeState( true ) );
		child->set_state( sg::DepthTestState( true ) );
		child->set_state( sg::BackfaceCullingState( true ) );

		child->attach( leaf );
		root->attach( child );

		// Check root.
		{
			sg::RenderState r_state;
			r_state.texture = texture;
			r_state.min_filter = GL_LINEAR_MIPMAP_NEAREST;
			r_state.mag_filter = GL_NEAREST_MIPMAP_LINEAR;
			r_state.wireframe = false;
			r_state.depth_test = false;
			r_state.backface_culling = false;

			BOOST_CHECK( root->get_render_state() == r_state );
		}

		// Check child + leaf.
		{
			sg::RenderState r_state;
			r_state.texture = texture2;
			r_state.min_filter = GL_NEAREST;
			r_state.mag_filter = GL_LINEAR;
			r_state.wireframe = true;
			r_state.depth_test = true;
			r_state.backface_culling = true;

			BOOST_CHECK( child->get_render_state() == r_state );
			BOOST_CHECK( leaf->get_render_state() == r_state );
		}
	}
}
