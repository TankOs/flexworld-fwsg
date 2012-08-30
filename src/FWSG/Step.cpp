#include <FWSG/Step.hpp>

namespace sg {

Step::Step(
	const RenderState& render_state,
	const FloatMatrix& transform_matrix,
	BufferObject::PtrConst buffer_object
) :
	m_render_state( render_state ),
	m_buffer_object( buffer_object ),
	m_transform_matrix( transform_matrix )
{
}

BufferObject::PtrConst Step::get_buffer_object() const {
	return m_buffer_object;
}

const FloatMatrix& Step::get_transform_matrix() const {
	return m_transform_matrix;
}

const RenderState& Step::get_render_state() const {
	return m_render_state;
}

}
