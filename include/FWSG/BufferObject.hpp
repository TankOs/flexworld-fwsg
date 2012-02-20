#pragma once

#include <FWSG/Vertex.hpp>
#include <FWSG/NonCopyable.hpp>

#include <SFML/OpenGL.hpp>
#include <vector>
#include <memory>

namespace sg {

/** Buffer object.
 * OpenGL buffer object for storing vertices, normals, texture coordinates and
 * colors.
 * The buffers are uploaded to the GPU only when upload() is called. All other
 * calls do not use OpenGL and can be therefore used in threads not having an
 * active OpenGL context.
 */
class BufferObject : public NonCopyable {
	public:
		typedef std::shared_ptr<BufferObject> Ptr; ///< Shared pointer.
		typedef std::shared_ptr<const BufferObject> PtrConst; ///< Shared pointer to const.

		/** Flags.
		 */
		enum Flag {
			VERTICES_ONLY = 0,
			NORMALS = 1 << 0,
			TEX_COORDS = 1 << 1,
			INDICES = 1 << 2
		};

		/** Ctor.
		 * @param flags Flags.
		 */
		BufferObject( int flags = VERTICES_ONLY );

		/** Dtor.
		 */
		~BufferObject();

		/** Add vertex.
		 * Only the properties of the vertex are used that were specified in the
		 * constructor's flags before.
		 * @param vertex Vertex.
		 */
		void add_vertex( const Vertex& vertex );

		/** Upload data to GPU.
		 * The internal buffers are cleared, i.e. added vertices.
		 */
		void upload();

		/** Render.
		 * Make sure to upload() before.
		 */
		void render() const;

		/** Check if buffer object needs upload.
		 * @return true if upload is needed.
		 */
		bool is_upload_needed() const;

		/** Get number of prepared vertices.
		 * @return Number of prepared vertices.
		 */
		std::size_t get_num_prepared_vertices() const;

		/** Get number of uploaded vertices.
		 * @return Number of uploaded vertices.
		 */
		std::size_t get_num_uploaded_vertices() const;

		/** Get prepared vertex.
		 * The returned vertex has set unused components to sg::Vertex' defaults.
		 * @param index (must be valid).
		 * @return Prepared vertex.
		 */
		sg::Vertex get_prepared_vertex( std::size_t index ) const;

	private:
		typedef std::vector<sf::Vector3f> Vector3Array;
		typedef std::vector<sf::Vector2f> Vector2Array;

		enum {
			VBO_INDEX = 0,
			NBO_INDEX,
			TBO_INDEX,
			IBO_INDEX,
			NUM_BUFFERS
		};

		Vector3Array m_vertices;
		Vector3Array m_normals;
		Vector2Array m_tex_coords;

		std::size_t m_num_vertices;
		int m_flags;

		GLuint m_buffers[NUM_BUFFERS];
};

}
