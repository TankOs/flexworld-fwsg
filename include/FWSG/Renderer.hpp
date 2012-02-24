#pragma once

#include <FWSG/RenderState.hpp>
#include <FWSG/Step.hpp>
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

	private:
		typedef std::vector<Step::Ptr> StepVector;

		struct RenderStateGroup {
			RenderState render_state;
			StepVector steps;
		};

		typedef std::vector<RenderStateGroup> GroupVector;

		GroupVector m_groups;
};

}
