#pragma once

#include <FWSG/RenderState.hpp>
#include <FWSG/Step.hpp>
#include <FWSG/StepProxy.hpp>
#include <FWSG/BufferObject.hpp>

#include <SFML/System/Mutex.hpp>
#include <vector>

namespace sg {

/** OpenGL renderer.
 *
 * The renderer is prepared to be used from multiple threads (e.g. to create
 * and prepare steps in one thread and render in another). Make sure to call
 * lock() and unlock() respectively before accessing ANY method in
 * multi-threaded environments.
 */
class Renderer {
	public:
		/** Ctor.
		 */
		Renderer();

		/** Dtor.
		 */
		~Renderer();

		/** Get number of render states.
		 * @return Number of render states.
		 */
		std::size_t get_num_render_states() const;

		/** Get number of steps.
		 * @return Number of steps.
		 */
		std::size_t get_num_steps() const;

		/** Create a new render step.
		 * It's safe to call this method from a thread not having an active OpenGL
		 * context. Buffer objects are uploaded in update() - besides of that the
		 * buffer objects aren't changed. Changing the buffer object after adding
		 * it to a step is not recommended. The renderer won't take notice of it
		 * and bad things can happen when you do it manually.
		 * @param render_state Render state the step belongs to.
		 * @param buffer_object Buffer object to render.
		 * @return Proxied step.
		 */
		StepProxy::Ptr create_step( const RenderState& render_state, BufferObject::Ptr buffer_object );

		/** Remove step (called automatically by proxy).
		 * @param proxy Step proxy.
		 */
		void remove_step( const StepProxy& proxy );

		/** Render.
		 */
		void render() const;

		/** Update.
		 * Always call this method prior to render so that prepared buffer objects
		 * get uploaded to the GPU.
		 */
		void update();

		/** Lock.
		 * A call to this method will block until a previous blocker releases the
		 * lock.
		 */
		void lock() const;

		/** Unlock.
		 * Call this only from the thread that locked the renderer!
		 */
		void unlock() const;

	private:
		typedef std::vector<Step::Ptr> StepVector;
		typedef std::vector<BufferObject::Ptr> BufferObjectVector;

		struct RenderStateGroup {
			RenderState render_state;
			StepVector steps;
		};

		struct GroupComparator {
			bool operator()( const RenderStateGroup* first, const RenderState& second );
			bool operator()( const RenderStateGroup* first, const RenderStateGroup* second );
		};

		typedef std::vector<RenderStateGroup*> GroupVector;

		GroupVector m_groups;
		BufferObjectVector m_uploadable_buffer_objects;
		mutable sf::Mutex m_mutex;
};

}
