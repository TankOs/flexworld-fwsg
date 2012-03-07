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
		 * @param transform Transform (reference is being held).
		 * @param buffer_object Buffer object.
		 */
		Step( const RenderState& render_state, const Transform& transform, BufferObject::PtrConst buffer_object );

		/** Get buffer object.
		 * @return Buffer object.
		 */
		BufferObject::PtrConst get_buffer_object() const;

		/** Get transform.
		 * @return Transform.
		 */
		const Transform& get_transform() const;

		/** Get render state.
		 * @return Render state.
		 */
		const RenderState& get_render_state() const;

	private:
		const RenderState m_render_state;
		BufferObject::PtrConst m_buffer_object;
		const sg::Transform& m_transform;
};

}
