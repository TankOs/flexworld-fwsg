#include <FWSG/NonCopyable.hpp>

namespace sg {

NonCopyable::NonCopyable() {
}

NonCopyable::NonCopyable( const NonCopyable& ) {
}

const NonCopyable& NonCopyable::operator=( const NonCopyable& ) {
	return *this;
}

}
