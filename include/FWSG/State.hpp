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
			PROGRAM_COMMAND = 0, ///< Shader program command.
			TEXTURE, ///< Texture.
			WIREFRAME, ///< Wireframe.
			DEPTH_TEST, ///< Depth test.
			FRUSTUM_CULLING, ///< Frustum culling.
			BACKFACE_CULLING, ///< Backface culling.
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
