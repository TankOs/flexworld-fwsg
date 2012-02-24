#include <FWSG/Renderer.hpp>

#include <algorithm>
#include <cassert>
#include <iostream> // XXX 

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

StepProxy::Ptr Renderer::create_step( const RenderState& render_state, BufferObject::PtrConst buffer_object ) {
	// Create step.
	Step::Ptr step( new Step( buffer_object ) );

	// Find render state.
	GroupVector::iterator bound_iter = std::lower_bound( m_groups.begin(), m_groups.end(), render_state );

	// Check if it's equal.
	if( bound_iter != m_groups.end() && bound_iter->render_state == render_state ) {
		std::cout << "Render state already there." << std::endl;
		bound_iter->steps.push_back( step );
	}
	else {
		std::cout << "New render state." << std::endl;

		// Not equal, insert new group.
		RenderStateGroup group;
		group.render_state = render_state;

		m_groups.push_back( group );
		m_groups.back().steps.push_back( step );

		// Sort.
		std::sort( m_groups.begin(), m_groups.end() );
	}

	// Create and return proxy.
	StepProxy::Ptr proxy( new StepProxy( step, *this ) );
	return proxy;
}

bool Renderer::RenderStateGroup::operator<( const RenderState& other ) const {
	return render_state < other;
}

bool Renderer::RenderStateGroup::operator<( const RenderStateGroup& other ) const {
	return render_state < other.render_state;
}

void Renderer::remove_step( const StepProxy& proxy ) {
	assert( &proxy.get_renderer() == this && "Step doesn't belong to this renderer." );

	// Find surrounding render state.
	StepVector::iterator step_iter;

	for( std::size_t state_idx = 0; state_idx < m_groups.size(); ++state_idx ) {
		step_iter = std::lower_bound( m_groups[state_idx].steps.begin(), m_groups[state_idx].steps.end(), proxy.get_step() );

		if( step_iter != m_groups[state_idx].steps.end() && *step_iter == proxy.get_step() ) {
			m_groups[state_idx].steps.erase( step_iter );

			// If this was the last step, kill group.
			if( m_groups[state_idx].steps.size() < 1 ) {
				m_groups.erase( m_groups.begin() + state_idx );
			}

			return;
		}
	}

	assert( 0 && "Step not registered." );
}

}
