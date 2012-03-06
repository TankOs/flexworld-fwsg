#include <GL/glew.h>
#include <FWSG/BufferObject.hpp>
#include <FWSG/Geometry.hpp>

#include <cstring>
#include <cassert>

namespace sg {

BufferObject::BufferObject( int flags, bool client_buffer ) :
	m_num_vertices( 0 ),
	m_flags( flags ),
	m_buffers( nullptr ),
	m_client_buffer( client_buffer )
{
	// Prepare memory for buffer IDs.
	if( !m_client_buffer ) {
		m_buffers = new GLuint[NUM_BUFFERS];
		std::memset( m_buffers, 0, sizeof( GLuint ) * NUM_BUFFERS );
	};
}

BufferObject::~BufferObject() {
	// Kill buffers.
	if( !m_client_buffer ) {
		release_buffers();
	}

	delete m_buffers;
}

void BufferObject::render() const {
	if( m_num_vertices < 1 ) {
		return;
	}

	// Enable needed client states and disable not needed ones.
	glEnableClientState( GL_VERTEX_ARRAY );

	if( (m_flags & NORMALS) == NORMALS ) {
		glEnableClientState( GL_NORMAL_ARRAY );
	}
	else {
		glDisableClientState( GL_NORMAL_ARRAY );
	}

	if( (m_flags & TEX_COORDS) == TEX_COORDS ) {
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	}
	else {
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	}

	if( (m_flags & INDICES) == INDICES ) {
		glEnableClientState( GL_INDEX_ARRAY );
	}
	else {
		glDisableClientState( GL_INDEX_ARRAY );
	}

	// TODO Implement!
	glDisableClientState( GL_COLOR_ARRAY );

	if( !m_client_buffer ) {
		// GPU mode, bind buffers and setup pointers.
		glBindBufferARB( GL_ARRAY_BUFFER, m_buffers[VBO_INDEX] );
		glVertexPointer( 3, GL_FLOAT, 0, 0 );

		if( (m_flags & NORMALS) == NORMALS ) {
			glBindBufferARB( GL_ARRAY_BUFFER, m_buffers[NBO_INDEX] );
			glNormalPointer( GL_FLOAT, 0, 0 );
		}

		if( (m_flags & TEX_COORDS) == TEX_COORDS ) {
			glBindBufferARB( GL_ARRAY_BUFFER, m_buffers[TBO_INDEX] );
			glTexCoordPointer( 2, GL_FLOAT, 0, 0 );
		}

		if( (m_flags & INDICES) == INDICES ) {
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, m_buffers[IBO_INDEX] );
		}
		else {
			// Unbind the buffer.
			glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, 0 );
		}

		glDrawElements( GL_TRIANGLES, static_cast<GLsizei>( m_num_vertices ), GL_UNSIGNED_SHORT, 0 );
	}
	else {
		glVertexPointer( 3, GL_FLOAT, 0, &m_vertices[0] );
		glNormalPointer( GL_FLOAT, 0, &m_normals[0] );
		glTexCoordPointer( 2, GL_FLOAT, 0, &m_tex_coords[0] );

		if( (m_flags & INDICES) == INDICES ) {
			glDrawElements( GL_TRIANGLES, static_cast<GLsizei>( m_num_vertices ), GL_UNSIGNED_SHORT, &m_indices[0] );
		}
		else {
			glDrawElements( GL_TRIANGLES, static_cast<GLsizei>( m_num_vertices ), GL_UNSIGNED_SHORT, 0 );
		}
	}
}

std::size_t BufferObject::get_num_vertices() const {
	return m_num_vertices;
}

bool BufferObject::is_client_buffer() const {
	return m_client_buffer;
}

void BufferObject::load( const Geometry& geometry ) {
	// Clear buffers and data.
	if( !m_client_buffer ) {
		release_buffers();
	}

	m_vertices.clear();
	m_normals.clear();
	m_tex_coords.clear();
	m_indices.clear();
	m_num_vertices = 0;

	if( (m_flags & INDICES) == 0 ) {
		// No-index mode, i.e. iterate over geometry's indices and add each vertex.
		// May be redundant because no vertices are shared.

		for( std::size_t index_idx = 0; index_idx < geometry.get_num_indices(); ++index_idx ) {
			const Vertex& vertex = geometry.get_vertex( geometry.get_index( index_idx ) );

			// Add data depending on flags.
			if( (m_flags & NORMALS) == NORMALS ) {
				m_normals.push_back( vertex.normal );
			}

			if( (m_flags & TEX_COORDS) == TEX_COORDS ) {
				m_tex_coords.push_back( vertex.uv );
			}

			// Add vertex vector.
			m_vertices.push_back( vertex.vector );
		}

		// Cache number of vertices.
		m_num_vertices = geometry.get_num_indices();
	}
	else {
		// Index mode. Add vertices but use the index buffer.
		for( uint32_t vertex_idx = 0; vertex_idx < geometry.get_num_vertices(); ++vertex_idx ) {
			const Vertex& vertex = geometry.get_vertex( vertex_idx );

			// Add data depending on flags.
			if( (m_flags & NORMALS) == NORMALS ) {
				m_normals.push_back( vertex.normal );
			}

			if( (m_flags & TEX_COORDS) == TEX_COORDS ) {
				m_tex_coords.push_back( vertex.uv );
			}

			// Add vertex vector.
			m_vertices.push_back( vertex.vector );
		}

		// Add indices.
		for( std::size_t index_idx = 0; index_idx < geometry.get_num_indices(); ++index_idx ) {
			m_indices.push_back( static_cast<GLushort>( geometry.get_index( index_idx ) ) );
		}

		// Save number of vertices.
		m_num_vertices = geometry.get_num_indices();
	}

	// In case of GPU mode we have to initialize and fill the buffers.
	if( !m_client_buffer ) {
		// VBO.
		glGenBuffersARB( 1, &m_buffers[VBO_INDEX] );
		glBindBufferARB( GL_ARRAY_BUFFER, m_buffers[VBO_INDEX] );
		glBufferDataARB( GL_ARRAY_BUFFER, m_num_vertices * sizeof( Vector3Array::value_type ), &m_vertices[0], GL_STATIC_DRAW );

		// NBO.
		if( m_flags & NORMALS ) {
			glGenBuffersARB( 1, &m_buffers[NBO_INDEX] );
			glBindBufferARB( GL_ARRAY_BUFFER, m_buffers[NBO_INDEX] );
			glBufferDataARB( GL_ARRAY_BUFFER, m_num_vertices * sizeof( Vector3Array::value_type ), &m_normals[0], GL_STATIC_DRAW );
		}

		// TBO.
		if( m_flags & TEX_COORDS ) {
			glGenBuffersARB( 1, &m_buffers[TBO_INDEX] );
			glBindBufferARB( GL_ARRAY_BUFFER, m_buffers[TBO_INDEX] );
			glBufferDataARB( GL_ARRAY_BUFFER, m_num_vertices * sizeof( Vector2Array::value_type ), &m_tex_coords[0], GL_STATIC_DRAW );
		}

		// Unbind buffers.
		glBindBufferARB( GL_ARRAY_BUFFER, 0 );
		glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER, 0 );

		// Delete local data buffers.
		m_vertices.clear();
		m_normals.clear();
		m_tex_coords.clear();
	}
}

void BufferObject::release_buffers() {
	assert( !m_client_buffer );

	// Release all buffers.
	for( std::size_t buffer_idx = 0; buffer_idx < NUM_BUFFERS; ++buffer_idx ) {
		if( m_buffers[buffer_idx] != 0 ) {
			glDeleteBuffersARB( 1, m_buffers + buffer_idx );
			m_buffers[buffer_idx] = 0;
		}
	}
}

}
