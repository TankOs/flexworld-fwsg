#include <FWSG/Leaf.hpp>
#include <FWSG/Node.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestLeaf ) {
	// Initial state.
	{
		sg::Leaf::Ptr leaf = sg::Leaf::create();

		BOOST_CHECK( leaf->get_parent() == false );
		BOOST_CHECK( leaf->get_local_translation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( leaf->get_local_rotation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( leaf->get_scale() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( leaf->get_global_translation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( leaf->get_global_rotation() == sf::Vector3f( 0, 0, 0 ) );
		BOOST_CHECK( leaf->is_update_needed() == true );
	}

	// Set transform.
	{
		sg::Leaf::Ptr leaf = sg::Leaf::create();

		leaf->set_local_translation( sf::Vector3f( 10, 11, 12 ) );
		leaf->set_local_rotation( sf::Vector3f( 20, 21, 22 ) );
		leaf->set_scale( sf::Vector3f( 30, 31, 32 ) );

		BOOST_CHECK( leaf->get_local_translation() == sf::Vector3f( 10, 11, 12 ) );
		BOOST_CHECK( leaf->get_local_rotation() == sf::Vector3f( 20, 21, 22 ) );
		BOOST_CHECK( leaf->get_scale() == sf::Vector3f( 30, 31, 32 ) );

		// No parent, so global == local.
		BOOST_CHECK( leaf->get_global_translation() == sf::Vector3f( 10, 11, 12 ) );
		BOOST_CHECK( leaf->get_global_rotation() == sf::Vector3f( 20, 21, 22 ) );
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

		root->add_child( child );
		child->add_child( leaf );

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
}
