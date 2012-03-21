#include <FWSG/Leaf.hpp>
#include <FWSG/Node.hpp>
#include <FWSG/TextureState.hpp>
#include <FWSG/WireframeState.hpp>
#include <FWSG/BackfaceCullingState.hpp>

#include <cassert>

namespace sg {

Leaf::Ptr Leaf::create() {
	Ptr leaf( new Leaf );
	return leaf;
}

Leaf::Leaf() :
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

void Leaf::recalculate_global_transform() {
	sg::Node::Ptr parent = m_parent.lock();

	if( parent ) {
		const sg::Transform& parent_global = parent->get_global_transform();

		m_global_transform = sg::Transform(
			parent_global.get_translation() + m_local_transform.get_translation(),
			parent_global.get_rotation() + m_local_transform.get_rotation(),
			sf::Vector3f(
				parent_global.get_scale().x * m_local_transform.get_scale().x,
				parent_global.get_scale().y * m_local_transform.get_scale().y,
				parent_global.get_scale().z * m_local_transform.get_scale().z
			),
			m_local_transform.get_origin()
		);
	}
	else {
		m_global_transform = m_local_transform;
	}

	handle_recalculate_global_transform();
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
	const BackfaceCullingState* backface_culling = find_state<BackfaceCullingState>();

	// Overwrite render states with found states.
	if( texture ) {
		m_render_state.texture = texture->get_texture();
	}

	if( wireframe ) {
		m_render_state.wireframe = wireframe->is_set();
	}

	if( backface_culling ) {
		m_render_state.backface_culling = backface_culling->is_set();
	}

	handle_update_render_state();
}

void Leaf::handle_update_render_state() {
}

void Leaf::set_local_transform( const sg::Transform& transform ) {
	m_local_transform = transform;
	recalculate_global_transform();
}

const sg::Transform& Leaf::get_local_transform() const {
	return m_local_transform;
}

const sg::Transform& Leaf::get_global_transform() const {
	return m_global_transform;
}

}
