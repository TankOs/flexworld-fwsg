#include <cassert>

namespace sg {

template <class StateType>
const StateType* Leaf::find_state() const {
	for( std::size_t state_idx = 0; state_idx < m_states.size(); ++state_idx ) {

		if( m_states[state_idx]->get_type() == StateType::TYPE_ID ) {
			const StateType* state = dynamic_cast<const StateType*>( m_states[state_idx] );
			return state;
		}

	}

	return nullptr;
}

template <class StateType>
void Leaf::reset_state() {
	for( std::size_t state_idx = 0; state_idx < m_states.size(); ++state_idx ) {

		if( m_states[state_idx]->get_type() == StateType::TYPE_ID ) {
			delete m_states[state_idx];
			m_states.erase( m_states.begin() + state_idx );

			update_render_state();

			return;
		}

	}

}

template <class StateType>
void Leaf::set_state( const StateType& state ) {
	// Make sure previous state is reset. Do NOT use reset_state() here as it
	// calls update_render_state() too which is unnecessary here.
	for( std::size_t state_idx = 0; state_idx < m_states.size(); ++state_idx ) {
		if( m_states[state_idx]->get_type() == StateType::TYPE_ID ) {
			// Found, delete and remove from array.
			delete m_states[state_idx];
			m_states.erase( m_states.begin() + state_idx );
			break;
		}
	}

	// Add new state and update render state.
	m_states.push_back( new StateType( state ) );
	update_render_state();
}

}
