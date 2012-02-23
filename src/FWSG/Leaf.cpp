#include <FWSG/Leaf.hpp>
#include <FWSG/Node.hpp>
#include <FWSG/TextureState.hpp>
#include <FWSG/WireframeState.hpp>

#include <cassert>

namespace sg {

Leaf::Ptr Leaf::create() {
	Ptr leaf( new Leaf );
	return leaf;
}

Leaf::Leaf() :
	m_global_translation( 0, 0, 0 ),
	m_global_rotation( 0, 0, 0 ),
	m_global_scale( 0, 0, 0 ),
	m_local_translation( 0, 0, 0 ),
	m_local_rotation( 0, 0, 0 ),
	m_scale( 0, 0, 0 ),
	m_needs_update( true )
{
}

Leaf::~Leaf() {
	// Kill states.
	for( std::size_t state_idx = 0; state_idx < m_states.size(); ++state_idx ) {
		delete m_states[state_idx];
	}

	m_states.clear();
}

void Leaf::set_parent( std::shared_ptr<Node> node ) {
	m_parent = node;
}

std::shared_ptr<Node> Leaf::get_parent() const {
	std::shared_ptr<Node> parent = m_parent.lock();
	return parent;
}

const sf::Vector3f& Leaf::get_local_translation() const {
	return m_local_translation;
}

const sf::Vector3f& Leaf::get_local_rotation() const {
	return m_local_rotation;
}

const sf::Vector3f& Leaf::get_scale() const {
	return m_scale;
}

bool Leaf::is_update_needed() const {
	return m_needs_update;
}

void Leaf::handle_update() {
}

void Leaf::update() {
	if( !m_needs_update ) {
		return;
	}

	handle_update();
	m_needs_update = false;
}

void Leaf::queue_update() {
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

const sf::Vector3f& Leaf::get_global_translation() const {
	return m_global_translation;
}

const sf::Vector3f& Leaf::get_global_rotation() const {
	return m_global_rotation;
}

void Leaf::set_local_translation( const sf::Vector3f& translation ) {
	m_local_translation = translation;
	recalculate_global_transform();
}

void Leaf::set_local_rotation( const sf::Vector3f& rotation ) {
	m_local_rotation = rotation;
	recalculate_global_transform();
}

void Leaf::recalculate_global_transform() {
	sg::Node::Ptr parent = m_parent.lock();

	if( parent ) {
		m_global_translation = parent->get_global_translation() + m_local_translation;
		m_global_rotation = parent->get_global_rotation() + m_local_rotation;
	}
	else {
		m_global_translation = m_local_translation;
		m_global_rotation = m_local_rotation;
	}

	handle_recalculate_global_transform();
}

void Leaf::set_scale( const sf::Vector3f& scale ) {
	m_scale = scale;
}

void Leaf::handle_recalculate_global_transform() {
}

std::size_t Leaf::get_num_states() const {
	return m_states.size();
}

bool Leaf::StateTypeComparator::operator()( const State* first, const State* second ) {
	return first->get_type() < second->get_type();
}

bool Leaf::StateTypeComparator::operator()( const State* first, const State::Type type ) {
	return first->get_type() < type;
}

const RenderState& Leaf::get_render_state() const {
	return m_render_state;
}

void Leaf::update_render_state() {
	Node::Ptr parent = m_parent.lock();

	if( parent ) {
		// Inherit render state from parent and overwrite by own states.
		m_render_state = parent->get_render_state();
	}
	else {
		// No parent, start with fresh render state.
		m_render_state = RenderState();
	}

	const TextureState* texture = find_state<TextureState>();
	const WireframeState* wireframe = find_state<WireframeState>();

	// Overwrite render states with found states.
	if( texture ) {
		m_render_state.texture = texture->get_texture();
	}

	if( wireframe ) {
		m_render_state.wireframe = wireframe->is_set();
	}

	handle_update_render_state();
}

void Leaf::handle_update_render_state() {
}

}
