#pragma once

#include <FWSG/NonCopyable.hpp>

#include <SFML/System/Vector3.hpp>
#include <memory>

namespace sg {

class Node;

/** Scene graph leaf.
 */
class Leaf : public NonCopyable {
	public:
		typedef std::shared_ptr<Leaf> Ptr; ///< Shared pointer.
		typedef std::shared_ptr<const Leaf> PtrConst; ///< Shared pointer to const.

		/** Create leaf.
		 * @return Leaf.
		 */
		static Ptr create();

		/** Dtor.
		 */
		virtual ~Leaf();

		/** Set parent.
		 * @param node Node.
		 */
		void set_parent( std::shared_ptr<Node> node );

		/** Get parent.
		 * @return Parent node or nullptr if no parent.
		 */
		std::shared_ptr<Node> get_parent() const;

		/** Get translation.
		 * @return Translation.
		 */
		const sf::Vector3f& get_translation() const;

		/** Get rotation.
		 * @return Rotation.
		 */
		const sf::Vector3f& get_rotation() const;

		/** Get scale.
		 * @return Scale.
		 */
		const sf::Vector3f& get_scale() const;

		/** Check if update is needed.
		 * @return true if update needed.
		 */
		bool is_update_needed() const;

		/** Update.
		 * Is only processed if this leaf is flagged for an update.
		 * @see handle_update() for defining behaviour.
		 */
		void update();

		/** Queue update.
		 */
		void queue_update();

	protected:
		/** Ctor.
		 */
		Leaf();

		/** Handle update (impl).
		 */
		virtual void handle_update();

	private:
		sf::Vector3f m_translation;
		sf::Vector3f m_rotation;
		sf::Vector3f m_scale;

		std::weak_ptr<Node> m_parent;

		bool m_needs_update;
};

}
