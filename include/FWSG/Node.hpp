#pragma once

#include <FWSG/Transform.hpp>
#include <FWSG/RenderState.hpp>
#include <FWSG/State.hpp>

#include <vector>
#include <memory>

namespace sg {

/** Node.
 */
class Node : public std::enable_shared_from_this<Node> {
	public:
		typedef std::shared_ptr<Node> Ptr; ///< Shared pointer.
		typedef std::shared_ptr<const Node> PtrConst; ///< Shared pointer to const.

		/** Create node.
		 * @return Node.
		 */
		static Ptr create();

		/** Dtor.
		 */
		virtual ~Node();

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
		const Transform& get_local_transform() const;

		/** Get global matrix.
		 * @return Global matrix.
		 */
		const FloatMatrix& get_global_matrix() const;

		/** Check if update is needed.
		 * @return true if update needed.
		 */
		bool is_update_needed() const;

		/** Update.
		 * Is only processed if this node is flagged for an update.
		 * @see handle_update() for defining behaviour.
		 */
		void update();

		/** Queue update.
		 */
		void queue_update();

		/** Recalculate global matrix.
		 */
		void recalculate_global_matrix();

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

		/** Get number of children.
		 * @return Number of children.
		 */
		std::size_t get_num_children() const;

		/** Attach a node.
		 * Undefined behaviour if node has already been added. The node must be in
		 * a detached state.
		 * @param node Node.
		 * @see has_child to check if a child has already been attached.
		 */
		void attach( Ptr node );

		/** Detach a node.
		 * Undefined behaviour if node hasn't been attached.
		 * @param node Node.
		 * @see has_child to check if a node has been attached.
		 */
		void detach( Ptr node );

		/** Check if child has been added (slow operation).
		 * @param node Node.
		 * @return true if added.
		 */
		bool has_child( Ptr node ) const;

	protected:
		/** Ctor.
		 */
		Node();

		/** Handle update (impl).
		 */
		virtual void handle_update();

		/** Handle recalculation of global matrix.
		 * Called after recalculate_global_matrix().
		 */
		virtual void handle_recalculate_global_matrix();

		/** Handle update of render state.
		 * Called after update_render_state().
		 */
		virtual void handle_update_render_state();

	private:
		typedef std::vector<Ptr> NodeVector;

		struct StateTypeComparator {
			bool operator()( const State* first, const State* second );
			bool operator()( const State* first, const State::Type type );
		};

		typedef std::vector<const State*> StateVector;

		RenderState m_render_state;
		NodeVector m_children;

		Transform m_local_transform;
		FloatMatrix m_global_matrix;
		sf::Vector3f m_scale;

		StateVector m_states;

		std::weak_ptr<Node> m_parent;

		bool m_needs_update;
};

}

#include "Node.inl"
