#pragma once

namespace sg {

/** Abstract state base class.
 * States are used for scene graph drawables to specify which render states
 * shall be set in the renderer.
 */
class State {
	public:
		/** State type.
		 */
		enum Type {
			SHADER = 0,
			TEXTURE,
			WIREFRAME,
			DEPTH_TEST,
			FRUSTUM_CULLING,
			BACKFACE_CULLING,
			NUM_TYPES
		};

		/** Dtor.
		 */
		virtual ~State();

		/** Get type.
		 * @return Type.
		 */
		Type get_type() const;

	protected:
		/** Ctor.
		 * @param type Type.
		 */
		State( Type type );

	private:
		Type m_type;
};

}
