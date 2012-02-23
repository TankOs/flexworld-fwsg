#include <FWSG/Node.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestNode ) {
	// Initial state.
	{
		sg::Node::Ptr node = sg::Node::create();

		BOOST_CHECK( node->get_parent() == false );
		BOOST_CHECK( node->get_translation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( node->get_rotation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( node->get_scale() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( node->is_update_needed() == true );

		BOOST_CHECK( node->get_num_children() == 0 );
	}

	// Update.
	{
		sg::Node::Ptr node = sg::Node::create();

		BOOST_CHECK( node->is_update_needed() == true );
		node->update();
		BOOST_CHECK( node->is_update_needed() == false );
	}

	// Add some children.
	{
		sg::Leaf::Ptr leaf0 = sg::Leaf::create();
		sg::Leaf::Ptr leaf1 = sg::Leaf::create();
		sg::Leaf::Ptr leaf2 = sg::Leaf::create();
		sg::Node::Ptr node = sg::Node::create();

		node->add_child( leaf0 );
		node->add_child( leaf1 );
		node->add_child( leaf2 );

		BOOST_CHECK( node->get_num_children() == 3 );
		BOOST_CHECK( node->has_child( leaf0 ) == true );
		BOOST_CHECK( node->has_child( leaf1 ) == true );
		BOOST_CHECK( node->has_child( leaf2 ) == true );

		BOOST_CHECK( leaf0->get_parent() == node );
		BOOST_CHECK( leaf1->get_parent() == node );
		BOOST_CHECK( leaf2->get_parent() == node );
	}

	// Delegation of update call.
	{
		sg::Leaf::Ptr leaf0 = sg::Leaf::create();
		sg::Leaf::Ptr leaf1 = sg::Leaf::create();
		sg::Leaf::Ptr leaf2 = sg::Leaf::create();
		sg::Node::Ptr node = sg::Node::create();

		node->add_child( leaf0 );
		node->add_child( leaf1 );
		node->add_child( leaf2 );

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

		root->add_child( child );
		root->update();

		BOOST_CHECK( root->is_update_needed() == false );
		BOOST_CHECK( child->is_update_needed() == false );
		BOOST_CHECK( leaf->is_update_needed() == true );

		child->add_child( leaf );

		BOOST_CHECK( root->is_update_needed() == true );
		BOOST_CHECK( child->is_update_needed() == true );
		BOOST_CHECK( leaf->is_update_needed() == true );
	}
}
