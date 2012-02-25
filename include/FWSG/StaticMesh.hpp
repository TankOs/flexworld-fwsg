#pragma once

#include <FWSG/Drawable.hpp>
#include <FWSG/BufferObject.hpp>
#include <FWSG/StepProxy.hpp>

#include <memory>

namespace sg {

/** Static mesh.
 */
class StaticMesh : public Drawable {
	public:
		typedef std::shared_ptr<StaticMesh> Ptr; ///< Shared pointer.
		typedef std::shared_ptr<const StaticMesh> PtrConst; ///< Shared pointer to const.

		/** Create.
		 * @param buffer_object Buffer object.
		 * @param renderer Renderer.
		 * @return Created StaticMesh.
		 */
		static Ptr create( BufferObject::PtrConst buffer_object, Renderer& renderer );

		/** Get buffer object.
		 * @return Buffer object.
		 */
		BufferObject::PtrConst get_buffer_object() const;

	protected:
		void handle_update();
		void handle_update_render_state();

	private:
		StaticMesh( BufferObject::PtrConst buffer_object, Renderer& renderer );

		void update_buffer_object();

		BufferObject::PtrConst m_buffer_object;
		StepProxy::Ptr m_step;
};

}
