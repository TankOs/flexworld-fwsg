#include <FWSG/StaticMesh.hpp>
#include <FWSG/Renderer.hpp>

namespace sg {

StaticMesh::Ptr StaticMesh::create( sg::BufferObject::PtrConst buffer_object, sg::Renderer& renderer ) {
	Ptr static_mesh( new StaticMesh( buffer_object, renderer ) );
	return static_mesh;
}

StaticMesh::StaticMesh( sg::BufferObject::PtrConst buffer_object, sg::Renderer& renderer ) :
	Drawable( renderer ),
	m_buffer_object( buffer_object )
{
}

BufferObject::PtrConst StaticMesh::get_buffer_object() const {
	return m_buffer_object;
}

void StaticMesh::handle_update() {
	invalidate_step();
}

void StaticMesh::handle_update_render_state() {
	invalidate_step();
}

void StaticMesh::invalidate_step() {
	m_step = get_renderer().create_step(
		get_render_state(),
		get_global_matrix(),
		m_buffer_object
	);
}

}
