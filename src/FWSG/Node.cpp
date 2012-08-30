#include <FWSG/Node.hpp>
#include <FWSG/TextureState.hpp>
#include <FWSG/WireframeState.hpp>
#include <FWSG/BackfaceCullingState.hpp>
#include <FWSG/DepthTestState.hpp>
#include <FWSG/ProgramCommandState.hpp>

#include <algorithm>
#include <cassert>

namespace sg {

Node::Ptr Node::create() {
	Ptr node( new Node );
	return node;
}

Node::Node() :
	m_needs_update( true )
{
}

Node::~Node() {
	// Cleanup memory.
	for( std::size_t state_idx = 0; state_idx < m_states.size(); ++state_idx ) {
		delete m_states[state_idx];
	}

	m_states.clear();
}

void Node::update() {
	if( !m_needs_update ) {
		return;
	}

	m_needs_update = false;
	handle_update();

	// Delegate to children.
	for( std::size_t child_idx = 0; child_idx < m_children.size(); ++child_idx ) {
		m_children[child_idx]->update();
	}
}

std::shared_ptr<Node> Node::get_parent() const {
	std::shared_ptr<Node> parent = m_parent.lock();
	return parent;
}

void Node::set_parent( std::shared_ptr<Node> node ) {
	m_parent = node;
}

bool Node::is_update_needed() const {
	return m_needs_update;
}

const RenderState& Node::get_render_state() const {
	return m_render_state;
}

void Node::set_local_transform( const sg::Transform& transform ) {
	m_local_transform = transform;
	recalculate_global_matrix();
}

const sg::Transform& Node::get_local_transform() const {
	return m_local_transform;
}

const FloatMatrix& Node::get_global_matrix() const {
	return m_global_matrix;
}

std::size_t Node::get_num_states() const {
	return m_states.size();
}

void Node::queue_update() {
	// Cancel if update is already queued.
	if( m_needs_update ) {
		return;
	}

	m_needs_update = true;

	// Queue at parent too, so it gets delegated down the hierarchy.
	Node::Ptr parent = m_parent.lock();
	if( parent ) {
		parent->queue_update();
	}
}

std::size_t Node::get_num_children() const {
	return m_children.size();
}

void Node::attach( Node::Ptr node ) {
	assert( node->get_parent() == false );
	assert( std::find( m_children.begin(), m_children.end(), node ) == m_children.end() );

	node->set_parent( shared_from_this() );
	m_children.push_back( node );

	// Queue update if child has update queued.
	if( node->is_update_needed() && !is_update_needed() ) {
		queue_update();
	}

	// Recalculate global matrix and update render state at child.
	node->recalculate_global_matrix();
	node->update_render_state();
}

void Node::recalculate_global_matrix() {
	sg::Node::Ptr parent = m_parent.lock();

	if( parent ) {
		m_global_matrix = parent->get_global_matrix();
		m_global_matrix.multiply( m_local_transform.get_matrix() );
	}
	else {
		m_global_matrix = m_local_transform.get_matrix();
	}

	// Delegate to children.
	for( std::size_t child_idx = 0; child_idx < m_children.size(); ++child_idx ) {
		m_children[child_idx]->recalculate_global_matrix();
	}
}

void Node::update_render_state() {
	Node::Ptr parent = m_parent.lock();

	if( parent ) {
		// Inherit render state from parent and overwrite by own states.
		m_render_state = parent->get_render_state();
	}
	else {
		// No parent, start with fresh render state.
		m_render_state = RenderState();
	}

	const ProgramCommandState* program_command = find_state<ProgramCommandState>();
	const TextureState* texture = find_state<TextureState>();
	const WireframeState* wireframe = find_state<WireframeState>();
	const BackfaceCullingState* backface_culling = find_state<BackfaceCullingState>();
	const DepthTestState* depth_test = find_state<DepthTestState>();

	// Overwrite render states with found states.
	if( program_command ) {
		m_render_state.program_command = program_command->get_program_command();
	}

	if( texture ) {
		m_render_state.texture = texture->get_texture();
	}

	if( wireframe ) {
		m_render_state.wireframe = wireframe->is_set();
	}

	if( backface_culling ) {
		m_render_state.backface_culling = backface_culling->is_set();
	}

	if( depth_test ) {
		m_render_state.depth_test = depth_test->is_set();
	}

	handle_update_render_state();

	// Delegate to children.
	for( std::size_t child_idx = 0; child_idx < m_children.size(); ++child_idx ) {
		m_children[child_idx]->update_render_state();
	}
}

void Node::detach( Node::Ptr node ) {
	assert( node->get_parent().get() == this );

	NodeVector::iterator node_iter = std::lower_bound( m_children.begin(), m_children.end(), node );
	assert( node_iter != m_children.end() && *node_iter == node );

	if( node_iter != m_children.end() && *node_iter == node ) {
		(*node_iter)->set_parent( Node::Ptr() );
		m_children.erase( node_iter );
	}
}

bool Node::has_child( Node::Ptr node ) const {
	return std::find( m_children.begin(), m_children.end(), node ) != m_children.end();
}

void Node::handle_recalculate_global_matrix() {
}

void Node::handle_update_render_state() {
}

void Node::handle_update() {
}

bool Node::StateTypeComparator::operator()( const State* first, const State* second ) {
	return first->get_type() < second->get_type();
}

bool Node::StateTypeComparator::operator()( const State* first, const State::Type type ) {
	return first->get_type() < type;
}

}
