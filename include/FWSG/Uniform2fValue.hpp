#pragma once

#include <FWSG/UniformValue.hpp>

namespace sg {

/** Uniform value specialization for float vectors with 2 components.
 */
class Uniform2fValue : public UniformValue {
	public:
		/** Ctor.
		 * @param location Location of uniform.
		 */
		Uniform2fValue( GLint location );

		/** Set value.
		 * @param x x.
		 * @param y y.
		 */
		void set( float x, float y );

		/** Get x value.
		 * @return x value.
		 */
		float get_x() const;

		/** Get y value.
		 * @return y value.
		 */
		float get_y() const;

		void apply();

	private:
		float m_x;
		float m_y;
};

}
