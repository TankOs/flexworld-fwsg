#pragma once

#include <FWSG/BufferObject.hpp>
#include <FWSG/RenderState.hpp>
#include <FWSG/NonCopyable.hpp>

#include <memory>

namespace sg {

class Transform;

/** Render step.
 * A render step is a concrete step executed during the rendering process. It
 * usually renders a single object using a buffer object.
 * The step also includes the transformations that shall be applied.
 */
class Step : public NonCopyable {
	public:
		typedef std::shared_ptr<Step> Ptr; ///< Shared pointer.
		typedef std::shared_ptr<const Step> PtrConst; ///< Shared pointer to const.

		/** Ctor.
		 * @param render_state Render state.
		 * @param global_transform Global transform (reference is being held).
		 * @param local_transform Local transform (reference is being held).
		 * @param buffer_object Buffer object.
		 */
		Step(
			const RenderState& render_state,
			const Transform& global_transform,
			const Transform& local_transform,
			BufferObject::PtrConst buffer_object
		);

		/** Get buffer object.
		 * @return Buffer object.
		 */
		BufferObject::PtrConst get_buffer_object() const;

		/** Get global transform.
		 * @return Global transform.
		 */
		const Transform& get_global_transform() const;

		/** Get local transform.
		 * @return Local transform.
		 */
		const Transform& get_local_transform() const;

		/** Get render state.
		 * @return Render state.
		 */
		const RenderState& get_render_state() const;

	private:
		const RenderState m_render_state;
		BufferObject::PtrConst m_buffer_object;
		const sg::Transform& m_global_transform;
		const sg::Transform& m_local_transform;
};

}
