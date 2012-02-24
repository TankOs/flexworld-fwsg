#include <FWSG/Renderer.hpp>

namespace sg {

Renderer::Renderer() {
}

std::size_t Renderer::get_num_render_states() const {
	return m_groups.size();
}

std::size_t Renderer::get_num_steps() const {
	std::size_t num = 0;

	for( std::size_t group_idx = 0; group_idx < m_groups.size(); ++group_idx ) {
		num += m_groups[group_idx].steps.size();
	}

	return num;
}

}
