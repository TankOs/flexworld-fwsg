#pragma once

#include <FWSG/State.hpp>

namespace sg {

/** Base class for simple boolean states.
 */
class BoolState : public State {
	public:
		/** Dtor.
		 */
		virtual ~BoolState();

		/** Check if state is set.
		 * @return true if set.
		 */
		bool is_set() const;

	protected:
		/** Ctor.
		 * @param type Type.
		 * @param value Value.
		 */
		BoolState( Type type, bool value );

	private:
		bool m_value;
};

}
