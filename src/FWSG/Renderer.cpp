#include <GL/glew.h>

#include <FWSG/Renderer.hpp>
#include <FWSG/Transform.hpp>

#include <algorithm>
#include <cassert>

namespace sg {

Renderer::Renderer() {
	glewInit();
}

Renderer::~Renderer() {
	lock();

	// Cleanup render states.
	for( std::size_t group_idx = 0; group_idx < m_groups.size(); ++group_idx ) {
		delete m_groups[group_idx];
	}

	m_groups.clear();

	unlock();
}

std::size_t Renderer::get_num_render_states() const {
	lock();
	std::size_t size = m_groups.size();
	unlock();

	return size;
}

std::size_t Renderer::get_num_steps() const {
	lock();

	std::size_t num = 0;

	for( std::size_t group_idx = 0; group_idx < m_groups.size(); ++group_idx ) {
		num += m_groups[group_idx]->steps.size();
	}

	unlock();

	return num;
}

StepProxy::Ptr Renderer::create_step(
	const RenderState& render_state,
	const Transform& global_transform,
	const Transform& local_transform,
	BufferObject::PtrConst buffer_object
) {
	lock();

	// Create step.
	Step::Ptr step( new Step( render_state, global_transform, local_transform, buffer_object ) );

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

	// Create proxy.
	StepProxy::Ptr proxy( new StepProxy( step, *this ) );

	unlock();

	return proxy;
}

void Renderer::remove_step( const StepProxy& proxy ) {
	lock();

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

			unlock();
			return;
		}
	}

	unlock();
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
	const sf::Texture* current_texture = nullptr;
	const int* min_filter = nullptr;
	const int* mag_filter = nullptr;
	const bool* wireframe = nullptr;
	const bool* backface_culling = nullptr;
	const bool* depth_test = nullptr;

	// Setup OpenGL.
	glMatrixMode( GL_MODELVIEW );
	glBindTexture( GL_TEXTURE_2D, 0 );
	glCullFace( GL_BACK );

	glDisable( GL_CULL_FACE );
	glDisable( GL_DEPTH_TEST );

	glEnable( GL_TEXTURE_2D );

	lock();

	for( group_idx = 0; group_idx < m_groups.size(); ++group_idx ) {
		state = &m_groups[group_idx]->render_state;
		steps = &m_groups[group_idx]->steps;

		// Texture.
		if( current_texture != state->texture.get() ) {
			current_texture = &*state->texture;

			if( current_texture ) {
				current_texture->bind();
			}
			else {
				glBindTexture( GL_TEXTURE_2D, 0 );
			}
		}

		// Texture filtering.
		if( min_filter == nullptr || *min_filter != state->min_filter ) {
			min_filter = &state->min_filter;

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, *min_filter );
		}

		if( mag_filter == nullptr || *mag_filter != state->mag_filter ) {
			mag_filter = &state->mag_filter;

			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, *mag_filter );
		}

		// Wireframe.
		if( wireframe == nullptr || *wireframe != state->wireframe ) {
			wireframe = &state->wireframe;

			glPolygonMode( GL_FRONT_AND_BACK, *wireframe ? GL_LINE : GL_FILL );
		}

		// Depth test.
		if( depth_test == nullptr || *depth_test != state->depth_test ) {
			depth_test = &state->depth_test;

			if( *depth_test ) {
				glEnable( GL_DEPTH_TEST );
			}
			else {
				glDisable( GL_DEPTH_TEST );
			}
		}

		// Backface culling.
		if( backface_culling == nullptr || *backface_culling != state->backface_culling ) {
			backface_culling = &state->backface_culling;

			if( *backface_culling ) {
				glEnable( GL_CULL_FACE );
			}
			else {
				glDisable( GL_CULL_FACE );
			}
		}

		for( step_idx = 0; step_idx < steps->size(); ++step_idx ) {
			step = (*steps)[step_idx].get();

			// Transform.
			glLoadIdentity();

			// Global transformation.
			glRotatef( step->get_global_transform().get_rotation().x, 1, 0, 0 );
			glRotatef( step->get_global_transform().get_rotation().y, 0, 1, 0 );
			glRotatef( step->get_global_transform().get_rotation().z, 0, 0, 1 );

			glTranslatef(
				step->get_global_transform().get_translation().x + step->get_local_transform().get_translation().x,
				step->get_global_transform().get_translation().y + step->get_local_transform().get_translation().y,
				step->get_global_transform().get_translation().z + step->get_local_transform().get_translation().z
			);

			// Local transformation.
			// Rotation.
			glRotatef( step->get_local_transform().get_rotation().x, 1, 0, 0 );
			glRotatef( step->get_local_transform().get_rotation().y, 0, 1, 0 );
			glRotatef( step->get_local_transform().get_rotation().z, 0, 0, 1 );

			// Scale.
			glScalef(
				step->get_local_transform().get_scale().x,
				step->get_local_transform().get_scale().y,
				step->get_local_transform().get_scale().z
			);

			// Origin.
			glTranslatef(
				-step->get_local_transform().get_origin().x,
				-step->get_local_transform().get_origin().y,
				-step->get_local_transform().get_origin().z
			);

			step->get_buffer_object()->render();
		}
	}

	unlock();
}

void Renderer::lock() const {
	m_mutex.lock();
}

void Renderer::unlock() const {
	m_mutex.unlock();
}

}
