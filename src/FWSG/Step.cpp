#include <FWSG/Step.hpp>

namespace sg {

Step::Step( const RenderState& render_state, const Transform& transform, BufferObject::PtrConst buffer_object ) :
	m_render_state( render_state ),
	m_buffer_object( buffer_object ),
	m_transform( transform )
{
}

BufferObject::PtrConst Step::get_buffer_object() const {
	return m_buffer_object;
}

const sg::Transform& Step::get_transform() const {
	return m_transform;
}

const RenderState& Step::get_render_state() const {
	return m_render_state;
}


}
