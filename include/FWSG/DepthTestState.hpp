#pragma once

#include <FWSG/BoolState.hpp>

namespace sg {

/** Depth test state.
 */
class DepthTestState : public BoolState {
	public:
		static const Type TYPE_ID; ///< DepthTest state type ID.

		/** Ctor.
		 * @param enable Enable depth test.
		 */
		DepthTestState( bool enable );
};

}
