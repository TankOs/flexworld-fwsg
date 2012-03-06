#pragma once

#include <FWSG/Vertex.hpp>
#include <FWSG/NonCopyable.hpp>

#include <SFML/OpenGL.hpp>
#include <vector>
#include <memory>

namespace sg {

class Geometry;

/** Buffer object.
 * OpenGL buffer object for storing vertices, normals, texture coordinates and
 * colors. The buffer object works in two ways:
 *
 *   * Client-side.
 *   * GPU-side.
 *
 * When in GPU mode, buffers get initialized and filled in the load() call.
 * All other methods except render() can be safely called from an
 * OpenGL-inactive thread.
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
			INDICES = 1 << 2,
			EVERYTHING = NORMALS | TEX_COORDS | INDICES
		};

		/** Ctor.
		 * @param flags Flags.
		 * @param client_buffer Stored at client? (false for GPU buffer object).
		 */
		BufferObject( int flags = VERTICES_ONLY, bool client_buffer = false );

		/** Dtor.
		 */
		~BufferObject();

		/** Render.
		 * Make sure to upload() before.
		 */
		void render() const;

		/** Get number of vertices.
		 * @return Number of vertices.
		 */
		std::size_t get_num_vertices() const;

		/** Check if buffer is stored at client.
		 * @return true if stored at client, false if stored at GPU.
		 */
		bool is_client_buffer() const;

		/** Load geometry into buffer object.
		 * This will also initialize and fill buffer objects (VBO, TBO, CBO, IBO).
		 * Be sure to NOT call this method from a thread not having an OpenGL
		 * context active.
		 * @param geometry Geometry.
		 */
		void load( const Geometry& geometry );

	private:
		typedef std::vector<sf::Vector3f> Vector3Array;
		typedef std::vector<sf::Vector2f> Vector2Array;
		typedef std::vector<GLushort> IndexArray;

		enum {
			VBO_INDEX = 0,
			NBO_INDEX,
			TBO_INDEX,
			IBO_INDEX,
			NUM_BUFFERS
		};

		void release_buffers();

		Vector3Array m_vertices;
		Vector3Array m_normals;
		Vector2Array m_tex_coords;
		IndexArray m_indices;

		std::size_t m_num_vertices;
		int m_flags;

		GLuint* m_buffers;

		bool m_client_buffer;
};

}
