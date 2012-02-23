#pragma once

#include <FWSG/Leaf.hpp>

#include <vector>

namespace sg {

/** Node.
 */
class Node : public Leaf, public std::enable_shared_from_this<Node> {
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

		/** Get number of children.
		 * @return Number of children.
		 */
		std::size_t get_num_children() const;

		/** Add child.
		 * Undefined behaviour if leaf has already been added. The leaf must be in
		 * a detached state.
		 * @param leaf Leaf.
		 * @see has_child to check if a child has already been added.
		 */
		void add_child( Leaf::Ptr leaf );

		/** Check if child has been added (slow operation).
		 * @param leaf Leaf.
		 * @return true if added.
		 */
		bool has_child( Leaf::Ptr leaf ) const;

	protected:
		/** Ctor.
		 */
		Node();

		virtual void handle_update();
		void handle_recalculate_global_transform();

	private:
		typedef std::vector<Leaf::Ptr> LeafVector;

		LeafVector m_children;
};

}
