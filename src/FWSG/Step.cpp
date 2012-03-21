#include <FWSG/Step.hpp>

namespace sg {

Step::Step(
	const RenderState& render_state,
	const Transform& global_transform,
	const Transform& local_transform,
	BufferObject::PtrConst buffer_object
) :
	m_render_state( render_state ),
	m_buffer_object( buffer_object ),
	m_global_transform( global_transform ),
	m_local_transform( local_transform )
{
}

BufferObject::PtrConst Step::get_buffer_object() const {
	return m_buffer_object;
}

const sg::Transform& Step::get_global_transform() const {
	return m_global_transform;
}

const sg::Transform& Step::get_local_transform() const {
	return m_local_transform;
}

const RenderState& Step::get_render_state() const {
	return m_render_state;
}


}
