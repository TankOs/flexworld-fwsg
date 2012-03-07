#pragma once

#include <FWSG/BufferObject.hpp>
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
		 * @param transform Transform (reference is being held).
		 * @param buffer_object Buffer object.
		 */
		Step( const Transform& transform, BufferObject::PtrConst buffer_object );

		/** Get buffer object.
		 * @return Buffer object.
		 */
		BufferObject::PtrConst get_buffer_object() const;

		/** Get transform.
		 * @return Transform.
		 */
		const sg::Transform& get_transform() const;

	private:
		BufferObject::PtrConst m_buffer_object;
		const sg::Transform& m_transform;
};

}
