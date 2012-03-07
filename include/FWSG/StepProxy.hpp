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
		 * @param auto_remove Auto-remove step from renderer when proxy gets destroyed.
		 */
		StepProxy( Step::Ptr step, Renderer& renderer, bool auto_remove = true );

		/** Dtor.
		 * Automatically unregisters step at renderer.
		 */
		~StepProxy();

		/** Get renderer.
		 * @return Renderer.
		 */
		Renderer& get_renderer() const;

		/** Get step.
		 * @return Const step.
		 */
		Step::PtrConst get_step() const;

	private:
		Step::Ptr m_step;
		Renderer& m_renderer;
		bool m_auto_remove;
};

}
