#pragma once

#include <FWSG/Node.hpp>

namespace sg {

class Renderer;

/** Abstract scene graph node used for rendering.
 */
class Drawable : public Node {
	public:
		/** Dtor.
		 */
		virtual ~Drawable();

		/** Get renderer.
		 * @return Renderer.
		 */
		Renderer& get_renderer() const;

	protected:
		/** Ctor.
		 * @param renderer Renderer to use.
		 */
		Drawable( Renderer& renderer );

	private:
		Renderer& m_renderer;
};

}
