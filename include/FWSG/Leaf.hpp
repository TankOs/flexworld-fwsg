#pragma once

#include <FWSG/NonCopyable.hpp>
#include <FWSG/RenderState.hpp>
#include <FWSG/State.hpp>
#include <FWSG/Transform.hpp>

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

		/** Set parent (for internal use!).
		 * @param node Node.
		 */
		void set_parent( std::shared_ptr<Node> node );

		/** Get parent.
		 * @return Parent node or nullptr if no parent.
		 */
		std::shared_ptr<Node> get_parent() const;

		/** Set local transform.
		 * @param transform Transform.
		 */
		void set_local_transform( const sg::Transform& transform );

		/** Get local transform.
		 * @return Local transform.
		 */
		const sg::Transform& get_local_transform() const;

		/** Get global transform.
		 * @return Global transform.
		 */
		const sg::Transform& get_global_transform() const;

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

		/** Update render state.
		 */
		void update_render_state();

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

		/** Get set of states (render state).
		 * @return Render state.
		 */
		const RenderState& get_render_state() const;

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

		/** Handle update of render state.
		 * Called after update_render_state().
		 */
		virtual void handle_update_render_state();

	private:
		struct StateTypeComparator {
			bool operator()( const State* first, const State* second );
			bool operator()( const State* first, const State::Type type );
		};

		typedef std::vector<const State*> StateVector;

		RenderState m_render_state;

		Transform m_global_transform;
		Transform m_local_transform;
		sf::Vector3f m_scale;

		StateVector m_states;

		std::weak_ptr<Node> m_parent;

		bool m_needs_update;
};

}

#include "Leaf.inl"
