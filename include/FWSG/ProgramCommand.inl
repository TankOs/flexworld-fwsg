namespace sg {

template <class T>
T* ProgramCommand::find_or_create_argument(
	const std::string& name,
	GLint location
) {
	NameIndexMap::iterator index_iter = m_name_indices.find( name );
	T* value = nullptr;

	// New argument?
	if( index_iter == m_name_indices.end() ) {
		value = new T( location );
		m_values.push_back( value );

		// Remember mapping.
		m_name_indices[name] = m_values.size() - 1;
	}
	else {
		// Dynamically cast to wanted type. If it fails re-create value with
		// correct type.
		value = dynamic_cast<T*>( m_values[index_iter->second] );

		if( !value ) {
			// Delete old value.
			delete m_values[index_iter->second];

			// Create and insert new value.
			value = new T( location );
			m_values[index_iter->second] = value;
		}
	}

	return value;
}

template <class T>
const T* ProgramCommand::find_argument(
	const std::string& name
) const {
	NameIndexMap::const_iterator index_iter = m_name_indices.find( name );

	if( index_iter == m_name_indices.end() ) {
		return nullptr;
	}

	return dynamic_cast<const T*>( m_values[index_iter->second] );
}

}
