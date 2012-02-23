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
			return;
		}

	}
}

template <class StateType>
void Leaf::set_state( const StateType& state ) {
	// Make sure previous state is reset.
	reset_state<StateType>();

	m_states.push_back( new StateType( state ) );
}

}
