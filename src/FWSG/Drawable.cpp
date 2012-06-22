#include <FWSG/Drawable.hpp>

namespace sg {

Drawable::~Drawable() {
}

Drawable::Drawable( Renderer& renderer ) :
	Node(),
	m_renderer( renderer )
{
}

Renderer& Drawable::get_renderer() const {
	return m_renderer;
}

}
