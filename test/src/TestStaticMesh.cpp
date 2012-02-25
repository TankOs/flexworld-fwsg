#include <FWSG/StaticMesh.hpp>
#include <FWSG/Renderer.hpp>
#include <FWSG/BufferObject.hpp>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( TestStaticMesh ) {
	// Initial state.
	{
		sg::Renderer renderer;
		sg::BufferObject::Ptr bo( new sg::BufferObject );

		sg::StaticMesh::Ptr mesh = sg::StaticMesh::create( bo, renderer );

		BOOST_CHECK( &mesh->get_renderer() == &renderer );
		BOOST_CHECK( mesh->get_buffer_object().get() == bo.get() );
	}
}
