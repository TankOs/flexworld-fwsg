#pragma once

#include <FWSG/BoolState.hpp>

namespace sg {

/** Wireframe state.
 */
class WireframeState : public BoolState {
	public:
		static const Type TYPE_ID; ///< Wireframe state type ID.

		/** Ctor.
		 * @param enable Enable wireframe.
		 */
		WireframeState( bool enable );
};

}
