#pragma once

#include <FWSG/Vertex.hpp>

#include <vector>
#include <cstdint>

namespace sg {

/** Base class for defining 3D geometry.
 *
 * Please use derived classes like TriangleGeometry.
 */
class Geometry {
	public:
		/** Geometry type.
		 */
		enum Type {
			TRIANGLES = 0, ///< Indices define triangles.
			QUADS ///< Indices define quads.
		};

		/** Ctor.
		 * @param type Type.
		 */
		Geometry( Type type = TRIANGLES );

		/** Dtor.
		 */
		virtual ~Geometry();

		/** Get type.
		 * @return Type.
		 */
		Type get_type() const;

		/** Get number of vertices.
		 * @return Number of vertices.
		 */
		std::size_t get_num_vertices() const;

		/** Get number of indices.
		 * @return Number of indices.
		 */
		std::size_t get_num_indices() const;

		/** Add vertex.
		 * @param vertex Vertex.
		 */
		void add_vertex( const Vertex& vertex );

		/** Add index.
		 * Undefined behaviour if invalid index is given.
		 * @param index Vertex index.
		 * @see get_num_vertices
		 */
		void add_index( uint32_t index );

		/** Get vertex.
		 * Undefined behaviour if index is invalid.
		 * @param index Index.
		 * @return Vertex.
		 * @see get_num_vertices
		 */
		const Vertex& get_vertex( uint32_t index );

		/** Get vertex index.
		 * Undefined behaviour if index is invalid.
		 * @param index Vertex-index index.
		 * @return Vertex-index.
		 * @see get_num_indices
		 */
		uint32_t get_index( std::size_t index ) const;

	private:
		typedef std::vector<sg::Vertex> VertexVector;
		typedef uint32_t VertexIndex;
		typedef std::vector<VertexIndex> IndexVector;

		VertexVector m_vertices;
		IndexVector m_indices;

		Type m_type;
};

}
