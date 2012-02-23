#include <FWSG/Leaf.hpp>
#include <FWSG/Node.hpp>

#include <cassert>

namespace sg {

Leaf::Ptr Leaf::create() {
	Ptr leaf( new Leaf );
	return leaf;
}

Leaf::Leaf() :
	m_translation( 0, 0, 0 ),
	m_rotation( 0, 0, 0 ),
	m_scale( 0, 0, 0 ),
	m_needs_update( true )
{
}

Leaf::~Leaf() {
}

void Leaf::set_parent( std::shared_ptr<Node> node ) {
	m_parent = node;
}

std::shared_ptr<Node> Leaf::get_parent() const {
	std::shared_ptr<Node> parent = m_parent.lock();
	return parent;
}

const sf::Vector3f& Leaf::get_translation() const {
	return m_translation;
}

const sf::Vector3f& Leaf::get_rotation() const {
	return m_rotation;
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

}
