#pragma once

#include <FWSG/NonCopyable.hpp>
#include <FWSG/State.hpp>

#include <SFML/System/Vector3.hpp>
#include <memory>
#include <vector>

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

		/** Set local translation.
		 * This will update the global translation, too.
		 * @param translation Translation.
		 */
		void set_local_translation( const sf::Vector3f& translation );

		/** Get local translation.
		 * @return Translation.
		 */
		const sf::Vector3f& get_local_translation() const;

		/** Set local rotation.
		 * This will update the global rotation, too.
		 * @param rotation Rotation.
		 */
		void set_local_rotation( const sf::Vector3f& rotation );

		/** Get local rotation.
		 * @return Rotation.
		 */
		const sf::Vector3f& get_local_rotation() const;

		/** Set scale.
		 * @param scale Scale.
		 */
		void set_scale( const sf::Vector3f& scale );

		/** Get scale.
		 * @return Scale.
		 */
		const sf::Vector3f& get_scale() const;

		/** Get global translation.
		 * @return Global translation.
		 */
		const sf::Vector3f& get_global_translation() const;

		/** Get global rotation.
		 * @return Global rotation.
		 */
		const sf::Vector3f& get_global_rotation() const;

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

		/** Recalculate global transform.
		 */
		void recalculate_global_transform();

		/** Get number of set states.
		 * @return Number of set states.
		 */
		std::size_t get_num_states() const;

		/** Find state by type.
		 * @return State or nullptr if not set.
		 */
		template <class StateType>
		const StateType* find_state() const;

		/** Set state.
		 * Previous states with the same type get overwritten.
		 * @param state State.
		 */
		template <class StateType>
		void set_state( const StateType& state );

		/** Reset state.
		 */
		template <class StateType>
		void reset_state();

	protected:
		/** Ctor.
		 */
		Leaf();

		/** Handle update (impl).
		 */
		virtual void handle_update();

		/** Handle recaculation of global transform.
		 * Called after recalculate_global_transform().
		 */
		virtual void handle_recalculate_global_transform();

	private:
		struct StateTypeComparator {
			bool operator()( const State* first, const State* second );
			bool operator()( const State* first, const State::Type type );
		};

		typedef std::vector<const State*> StateVector;

		sf::Vector3f m_global_translation;
		sf::Vector3f m_global_rotation;
		sf::Vector3f m_global_scale;
		sf::Vector3f m_local_translation;
		sf::Vector3f m_local_rotation;
		sf::Vector3f m_scale;

		StateVector m_states;

		std::weak_ptr<Node> m_parent;

		bool m_needs_update;
};

}

#include "Leaf.inl"
