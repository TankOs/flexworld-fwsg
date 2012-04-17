#pragma once

#include <SFML/OpenGL.hpp>
#include <string>
#include <memory>
#include <vector>
#include <map>

namespace sg {

class Program;
class UniformValue;

/** Program command.
 *
 * The command holds a reference to the actual shader program together with
 * program arguments.
 *
 * When setting arguments it's only checked if the uniform with the given name
 * exists and is registered within the program. Make sure to use the correct
 * data type (OpenGL doesn't provide anything to check for the correct type, so
 * doesn't FWSG).
 */
class ProgramCommand {
	public:
		typedef std::shared_ptr<ProgramCommand> Ptr; ///< Shared pointer.
		typedef std::shared_ptr<const ProgramCommand> PtrConst; ///< Shared pointer to const.

		/** Ctor.
		 * @param program Program.
		 */
		ProgramCommand( std::shared_ptr<const Program> program );

		/** Dtor.
		 */
		~ProgramCommand();

		/** Get program.
		 * @return Program.
		 */
		std::shared_ptr<const Program> get_program() const;

		/** Get number of arguments.
		 * @return Number of arguments.
		 */
		std::size_t get_num_arguments() const;

		/** Set argument (float, solo).
		 * @param name Name.
		 * @param value Value.
		 */
		void set_argument( const std::string& name, float value );

		/** Set argument (float vector, 2 components).
		 * @param name Name.
		 * @param x x.
		 * @param y y.
		 */
		void set_argument( const std::string& name, float x, float y );

		/** Set argument (float vector, 3 components).
		 * @param name Name.
		 * @param x x.
		 * @param y y.
		 * @param z z.
		 */
		void set_argument( const std::string& name, float x, float y, float z );

		/** Set argument (float vector, 4 components).
		 * @param name Name.
		 * @param x x.
		 * @param y y.
		 * @param z z.
		 * @param w w.
		 */
		void set_argument( const std::string& name, float x, float y, float z, float w );

		/** Find an argument.
		 * @param name Name.
		 * @return Argument or nullptr if not found or type mismatch.
		 */
		template <class T>
		const T* find_argument( const std::string& name ) const;

		/** Get argument by index.
		 * Undefined behaviour if index is invalid.
		 * @param index Index.
		 * @return Argument.
		 */
		const UniformValue* get_argument( std::size_t index ) const;

	private:
		typedef std::map<const std::string, std::size_t> NameIndexMap;
		typedef std::vector<UniformValue*> UniformValueArray;

		template <class T>
		T* find_or_create_argument( const std::string& name, GLint location );

		NameIndexMap m_name_indices;
		UniformValueArray m_values;
		std::shared_ptr<const Program> m_program;
};

}

#include "ProgramCommand.inl"
