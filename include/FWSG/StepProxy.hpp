#pragma once

#include <FWSG/Step.hpp>

#include <memory>

namespace sg {

class Renderer;

/** Proxy class for working with a renderer step.
 */
class StepProxy {
	public:
		typedef std::shared_ptr<StepProxy> Ptr; ///< Shared pointer.
		typedef std::shared_ptr<const StepProxy> PtrConst; ///< Shared pointer to const.

		/** Ctor.
		 * @param step Step.
		 * @param renderer Renderer.
		 */
		StepProxy( Step::Ptr step, Renderer& renderer );

		/** Get renderer.
		 * @return Renderer.
		 */
		Renderer& get_renderer() const;

		/** Get step.
		 * @return Const step.
		 */
		Step::PtrConst get_step() const;

		/** Set step's translation and notify renderer.
		 * @param translation Translation.
		 */
		void set_translation( const sf::Vector3f& translation );

		/** Set step's rotation and notify renderer.
		 * @param rotation Rotation.
		 */
		void set_rotation( const sf::Vector3f& rotation );

		/** Set step's scale and notify renderer.
		 * @param scale Scale.
		 */
		void set_scale( const sf::Vector3f& scale );

	private:
		Step::Ptr m_step;
		Renderer& m_renderer;
};

}
