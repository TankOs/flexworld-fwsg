#pragma once

#include <FWSG/UniformValue.hpp>

namespace sg {

/** Uniform value specialization for single floats.
 */
class Uniform1fValue : public UniformValue {
	public:
		/** Ctor.
		 * @param location Location of uniform.
		 */
		Uniform1fValue( GLint location );

		/** Set value.
		 * @param value Value.
		 */
		void set( float value );

		/** Get value.
		 * @return Value.
		 */
		float get() const;

		void apply();

	private:
		float m_value;
};

}
