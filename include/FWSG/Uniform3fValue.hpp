#pragma once

#include <FWSG/UniformValue.hpp>

namespace sg {

/** Uniform value specialization for float vectors with 3 components.
 */
class Uniform3fValue : public UniformValue {
	public:
		/** Ctor.
		 * @param location Location of uniform.
		 */
		Uniform3fValue( GLint location );

		/** Set value.
		 * @param x x.
		 * @param y y.
		 * @param z z.
		 */
		void set( float x, float y, float z );

		/** Get x value.
		 * @return x value.
		 */
		float get_x() const;

		/** Get y value.
		 * @return y value.
		 */
		float get_y() const;

		/** Get z value.
		 * @return z value.
		 */
		float get_z() const;

		void apply();

	private:
		float m_x;
		float m_y;
		float m_z;
};

}
