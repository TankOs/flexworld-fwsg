#include <FWSG/Renderer.hpp>

#include <algorithm>
#include <cassert>
#include <iostream> // XXX 

namespace sg {

Renderer::Renderer() {
}

Renderer::~Renderer() {
	// Cleanup render states.
	for( std::size_t group_idx = 0; group_idx < m_groups.size(); ++group_idx ) {
		delete m_groups[group_idx];
	}
}

std::size_t Renderer::get_num_render_states() const {
	return m_groups.size();
}

std::size_t Renderer::get_num_steps() const {
	std::size_t num = 0;

	for( std::size_t group_idx = 0; group_idx < m_groups.size(); ++group_idx ) {
		num += m_groups[group_idx]->steps.size();
	}

	return num;
}

StepProxy::Ptr Renderer::create_step( const RenderState& render_state, BufferObject::PtrConst buffer_object ) {
	// Create step.
	Step::Ptr step( new Step( buffer_object ) );

	// Find render state.
	GroupVector::iterator bound_iter = std::lower_bound( m_groups.begin(), m_groups.end(), render_state, GroupComparator() );

	// Check if it's equal.
	if( bound_iter != m_groups.end() && (*bound_iter)->render_state == render_state ) {
		(*bound_iter)->steps.push_back( step );
		std::sort( (*bound_iter)->steps.begin(), (*bound_iter)->steps.end() );
	}
	else {
		// Not equal, insert new group.
		RenderStateGroup* group = new RenderStateGroup;
		group->render_state = render_state;

		m_groups.push_back( group );
		m_groups.back()->steps.push_back( step );
		std::sort( m_groups.back()->steps.begin(), m_groups.back()->steps.end() );

		// Sort.
		std::sort( m_groups.begin(), m_groups.end(), GroupComparator() );
	}

	// Create and return proxy.
	StepProxy::Ptr proxy( new StepProxy( step, *this ) );
	return proxy;
}

void Renderer::remove_step( const StepProxy& proxy ) {
	assert( &proxy.get_renderer() == this && "Step doesn't belong to this renderer." );

	// Find surrounding render state.
	StepVector::iterator step_iter;

	for( std::size_t state_idx = 0; state_idx < m_groups.size(); ++state_idx ) {
		step_iter = std::lower_bound( m_groups[state_idx]->steps.begin(), m_groups[state_idx]->steps.end(), proxy.get_step() );

		if( step_iter != m_groups[state_idx]->steps.end() && *step_iter == proxy.get_step() ) {
			m_groups[state_idx]->steps.erase( step_iter );

			// If this was the last step, kill group.
			if( m_groups[state_idx]->steps.size() < 1 ) {
				delete m_groups[state_idx];
				m_groups.erase( m_groups.begin() + state_idx );
			}

			return;
		}
	}

	assert( 0 && "Step not registered." );
}

bool Renderer::GroupComparator::operator()( const RenderStateGroup* first, const RenderState& second ) {
	return first->render_state < second;
}

bool Renderer::GroupComparator::operator()( const RenderStateGroup* first, const RenderStateGroup* second ) {
	return first->render_state < second->render_state;
}

void Renderer::render() const {
	std::size_t group_idx = 0;
	std::size_t step_idx = 0;
	const RenderState* state = nullptr;
	const StepVector* steps = nullptr;
	const Step* step = nullptr;
	const sf::Texture* current_texture = 0;
	const bool* wireframe = nullptr;

	// Setup OpenGL.
	glMatrixMode( GL_MODELVIEW );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glCullFace( GL_BACK );
	glEnable( GL_CULL_FACE );

	for( group_idx = 0; group_idx < m_groups.size(); ++group_idx ) {
		state = &m_groups[group_idx]->render_state;
		steps = &m_groups[group_idx]->steps;

		// Texture.
		if( current_texture != state->texture.get() ) {
			current_texture = &*state->texture;

			if( current_texture ) {
				current_texture->Bind();
			}
			else {
				glBindTexture( GL_TEXTURE_2D, 0 );
			}
		}

		// Wireframe.
		if( wireframe == nullptr || *wireframe != state->wireframe ) {
			wireframe = &state->wireframe;

			glPolygonMode( GL_FRONT_AND_BACK, *wireframe ? GL_LINE : GL_FILL );
		}

		for( step_idx = 0; step_idx < steps->size(); ++step_idx ) {
			step = (*steps)[step_idx].get();

			// Transform.
			glLoadIdentity();
			glTranslatef(
				step->get_translation().x,
				step->get_translation().y,
				step->get_translation().z
			);

			// Render.
			step->get_buffer_object()->render();
		}
	}

	// Restore OpenGL states.
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

}