#include <FWSG/State.hpp>

#include <memory>

namespace sg {

class ProgramCommand;

/** Program command state.
 *
 * Used to enable shaders together with coupled arguments.
 *
 * You can't change the shader program once the state has been set, however
 * changing the arguments is perfectly fine.
 */
class ProgramCommandState : public State {
	public:
		typedef std::shared_ptr<const ProgramCommand> ProgramCommandPtrConst; ///< Shared pointer to const ProgramCommand.

		static const Type TYPE_ID; ///< Texture state type ID.

		/** Ctor.
		 * Undefined behaviour if program_command is null.
		 * @param program_command Program command.
		 */
		ProgramCommandState( ProgramCommandPtrConst program_command );

		/** Get Program command.
		 * @return Program command.
		 */
		ProgramCommandPtrConst get_program_command() const;

	private:
		ProgramCommandPtrConst m_program_command;
};

}
