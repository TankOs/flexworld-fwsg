#pragma once

#include <FWSG/BoolState.hpp>

namespace sg {

/** BackfaceCulling state.
 */
class BackfaceCullingState : public BoolState {
	public:
		static const Type TYPE_ID; ///< BackfaceCulling state type ID.

		/** Ctor.
		 * @param enable Enable wireframe.
		 */
		BackfaceCullingState( bool enable );
};

}
