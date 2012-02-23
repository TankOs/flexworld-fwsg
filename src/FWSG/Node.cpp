#include <FWSG/Node.hpp>

#include <algorithm>
#include <cassert>

namespace sg {

Node::Ptr Node::create() {
	Ptr node( new Node );
	return node;
}

Node::Node() :
	Leaf()
{
}

Node::~Node() {
}

void Node::handle_update() {
	// Delegate to children.
	for( std::size_t child_idx = 0; child_idx < m_children.size(); ++child_idx ) {
		m_children[child_idx]->update();
	}
}

std::size_t Node::get_num_children() const {
	return m_children.size();
}

void Node::add_child( Leaf::Ptr leaf ) {
	assert( leaf->get_parent() == false );
	assert( std::find( m_children.begin(), m_children.end(), leaf ) == m_children.end() );

	leaf->set_parent( shared_from_this() );
	m_children.push_back( leaf );

	// Queue update if child has update queued.
	if( leaf->is_update_needed() && !is_update_needed() ) {
		queue_update();
	}

	// Recalculate global transform at child.
	leaf->recalculate_global_transform();
}

bool Node::has_child( Leaf::Ptr leaf ) const {
	return std::find( m_children.begin(), m_children.end(), leaf ) != m_children.end();
}

void Node::handle_recalculate_global_transform() {
	// Delegate to children.
	for( std::size_t child_idx = 0; child_idx < m_children.size(); ++child_idx ) {
		m_children[child_idx]->recalculate_global_transform();
	}
}

}