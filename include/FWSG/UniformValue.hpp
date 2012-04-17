#pragma once

#include <SFML/OpenGL.hpp>

namespace sg {

/** Abstract base class for uniform values.
 *
 * Each specialization of this class implements setting the proper uniform
 * value through OpenGL in the apply() method.
 */
class UniformValue {
	public:
		/** Dtor.
		 */
		virtual ~UniformValue();

		/** Get location.
		 * @return Location.
		 */
		GLint get_location() const;

		/** Apply value to uniform.
		 */
		virtual void apply() = 0;

	protected:
		/** Ctor.
		 * @param location Location of uniform.
		 */
		UniformValue( GLint location );

	private:
		GLint m_location;
};

}
