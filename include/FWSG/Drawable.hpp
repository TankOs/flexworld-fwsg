#pragma once

#include <FWSG/Leaf.hpp>

namespace sg {

class Renderer;

/** Abstract scene graph leaf used for rendering.
 */
class Drawable : public Leaf {
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
