#pragma once

#include <FWSG/RenderState.hpp>
#include <FWSG/Step.hpp>
#include <FWSG/StepProxy.hpp>
#include <FWSG/BufferObject.hpp>

#include <vector>

namespace sg {

/** OpenGL renderer.
 */
class Renderer {
	public:
		/** Ctor.
		 */
		Renderer();

		/** Get number of render states.
		 * @return Number of render states.
		 */
		std::size_t get_num_render_states() const;

		/** Get number of steps.
		 * @return Number of steps.
		 */
		std::size_t get_num_steps() const;

		/** Create a new render step.
		 * @param render_state Render state the step belongs to.
		 * @param buffer_object Buffer object to render.
		 * @return Proxied step.
		 */
		StepProxy::Ptr create_step( const RenderState& render_state, BufferObject::PtrConst buffer_object );

	private:
		typedef std::vector<Step::Ptr> StepVector;

		struct RenderStateGroup {
			bool operator<( const RenderState& other ) const;
			bool operator<( const RenderStateGroup& other ) const;

			RenderState render_state;
			StepVector steps;
		};

		typedef std::vector<RenderStateGroup> GroupVector;

		GroupVector m_groups;
};

}
