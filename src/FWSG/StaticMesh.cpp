#include <FWSG/StaticMesh.hpp>
#include <FWSG/Renderer.hpp>

#include <iostream> // XXX 

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
	update_buffer_object();
}

void StaticMesh::handle_update_render_state() {
	update_buffer_object();
}

void StaticMesh::update_buffer_object() {
	m_step = get_renderer().create_step( get_render_state(), m_buffer_object );

	// Apply transformation.
	m_step->set_translation( get_global_translation() );
	m_step->set_rotation( get_global_rotation() );
	m_step->set_scale( get_scale() );
}

}
