#pragma once

#include <FWSG/BoolState.hpp>

namespace sg {

/** Wireframe state.
 */
class WireframeState : public BoolState {
	public:
		/** Ctor.
		 * @param enable Enable wireframe.
		 */
		WireframeState( bool enable );
};

}
