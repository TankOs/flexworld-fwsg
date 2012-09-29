#pragma once

#include <FWSG/Geometry.hpp>

namespace sg {

/** Geometry build of triangles.
 *
 * Use the *_triangle methods to modify the geometry.
 */
class TriangleGeometry : public Geometry {
	public:
		/** Ctor.
		 */
		TriangleGeometry();

		/** Add triangle.
		 * This method will try to re-use same vertices added before. This can be
		 * slightly slower. If you don't want/need this optimization (which reduces
		 * the vertex count) you can disable it in the arguments.
		 * @param a Vertex 0.
		 * @param b Vertex 1.
		 * @param c Vertex 2.
		 * @param reuse Reuse same previously added vertices.
		 */
		void add_triangle( const Vertex& a, const Vertex& b, const Vertex& c, bool reuse = true );

		/** Get number of triangles.
		 * @return Number of triangles.
		 */
		std::size_t get_num_triangles() const;

	private:
};

}
