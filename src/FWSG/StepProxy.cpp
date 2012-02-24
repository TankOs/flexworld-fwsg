#include <FWSG/StepProxy.hpp>
#include <FWSG/Renderer.hpp>

namespace sg {

StepProxy::StepProxy( Step::Ptr step, Renderer& renderer, bool auto_remove ) :
	m_step( step ),
	m_renderer( renderer ),
	m_auto_remove( auto_remove )
{
}

StepProxy::~StepProxy() {
	if( m_auto_remove ) {
		m_renderer.remove_step( *this );
	}
}

Renderer& StepProxy::get_renderer() const {
	return m_renderer;
}

Step::PtrConst StepProxy::get_step() const {
	return m_step;
}

void StepProxy::set_translation( const sf::Vector3f& translation ) {
	m_step->set_translation( translation );
	// TODO: Notify renderer.
}

void StepProxy::set_rotation( const sf::Vector3f& rotation ) {
	m_step->set_rotation( rotation );
	// TODO: Notify renderer.
}

void StepProxy::set_scale( const sf::Vector3f& scale ) {
	m_step->set_scale( scale );
	// TODO: Notify renderer.
}

}
