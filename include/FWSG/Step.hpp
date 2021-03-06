#pragma once

#include <FWSG/BufferObject.hpp>
#include <FWSG/RenderState.hpp>

#include <FWU/Matrix.hpp>
#include <memory>

namespace sg {

class Transform;

/** Render step.
 * A render step is a concrete step executed during the rendering process. It
 * usually renders a single object using a buffer object.
 * The step also includes the transformations that shall be applied.
 */
class Step {
	public:
		typedef std::shared_ptr<Step> Ptr; ///< Shared pointer.
		typedef std::shared_ptr<const Step> PtrConst; ///< Shared pointer to const.

		/** Ctor.
		 * @param render_state Render state.
		 * @param transform_matrix Transform matrix (referenced!).
		 * @param buffer_object Buffer object.
		 */
		Step(
			const RenderState& render_state,
			const util::FloatMatrix& transform_matrix,
			BufferObject::PtrConst buffer_object
		);

		/** Copy ctor.
		 * @param other Other.
		 */
		Step( const Step& other ) = delete;

		/** Assignment.
		 * @param other Other.
		 */
		Step& operator=( const Step& other ) = delete;

		/** Get buffer object.
		 * @return Buffer object.
		 */
		BufferObject::PtrConst get_buffer_object() const;

		/** Get transform matrix.
		 * @return Transform matrix.
		 */
		const util::FloatMatrix& get_transform_matrix() const;

		/** Get render state.
		 * @return Render state.
		 */
		const RenderState& get_render_state() const;

	private:
		const RenderState m_render_state;
		BufferObject::PtrConst m_buffer_object;
		const util::FloatMatrix& m_transform_matrix;
};

}
