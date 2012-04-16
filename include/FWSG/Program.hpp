#pragma once

#include <FWSG/NonCopyable.hpp>

#include <SFML/OpenGL.hpp>
#include <map>
#include <vector>
#include <string>

namespace sg {

/** Program containing shaders.
 *
 * The Program class in FWSG represents an OpenGL program with one or multiple
 * sources. Vertex and fragment shaders can be combined.
 *
 * Uniforms can be set via the appropriate functions. They must be registered
 * before they can be used.
 *
 * At any time sources can be added. Just make sure to link the program before
 * it's being used. Removing sources is not possible.
 */
class Program : public NonCopyable {
	public:
		/** Shader type.
		 */
		enum ShaderType {
			VERTEX_SHADER = 0, ///< Vertex shader.
			FRAGMENT_SHADER, ///< Fragment shader.
			NUM_SHADER_TYPES ///< Number of types.
		};

		/** Ctor.
		 */
		Program();

		/** Dtor.
		 */
		~Program();

		/** Program linked?
		 * @return true if linked.
		 */
		bool is_linked() const;

		/** Get number of successfully registered uniforms.
		 * @return Number of uniforms.
		 */
		std::size_t get_num_uniforms() const;

		/** Get number of shaders.
		 * @return Number of shaders.
		 */
		std::size_t get_num_shaders() const;

		/** Add shader.
		 * The source code will be directly compiled. The previously linked program
		 * (if it exists) will be deleted. Same goes for registered uniforms.
		 * @param source Source code.
		 * @param type Shader type.
		 * @return true on success.
		 */
		bool add_shader( const std::string& source, ShaderType type );

		/** Link shaders.
		 * The previous linked program will be deleted, no matter if the linking
		 * fails or succeeds.
		 * @return true on success.
		 */
		bool link();

		/** Register uniform.
		 * Only valid when program has been linked before.
		 * @param name Name.
		 * @return true on success.
		 */
		bool register_uniform( const std::string& name );

		/** Check if a uniform was registered.
		 * @param name Name.
		 * @return true if registered.
		 */
		bool is_uniform_registered( const std::string& name ) const;

		/** Use.
		 * Must be linked before.
		 */
		void use() const;

		/** Set uniform (single float variable).
		 * @param name Name of uniform.
		 * @param value Value.
		 * @return true on success.
		 */
		bool set_uniform( const std::string& name, float value );

		/** Set uniform (vec2).
		 * @param name Name of uniform.
		 * @param x x value.
		 * @param y y value.
		 * @return true on success.
		 */
		bool set_uniform( const std::string& name, float x, float y );

		/** Set uniform (vec3).
		 * @param name Name of uniform.
		 * @param x x value.
		 * @param y y value.
		 * @param z z value.
		 * @return true on success.
		 */
		bool set_uniform( const std::string& name, float x, float y, float z );

		/** Set uniform (vec4).
		 * @param name Name of uniform.
		 * @param x x value.
		 * @param y y value.
		 * @param z z value.
		 * @param w w value.
		 * @return true on success.
		 */
		bool set_uniform( const std::string& name, float x, float y, float z, float w );

		/** Set uniform (single int variable).
		 * @param name Name of uniform.
		 * @param value Value.
		 * @return true on success.
		 */
		bool set_uniform( const std::string& name, int value );

		/** Set uniform (vec2).
		 * @param name Name of uniform.
		 * @param x x value.
		 * @param y y value.
		 * @return true on success.
		 */
		bool set_uniform( const std::string& name, int x, int y );

		/** Set uniform (vec3).
		 * @param name Name of uniform.
		 * @param x x value.
		 * @param y y value.
		 * @param z z value.
		 * @return true on success.
		 */
		bool set_uniform( const std::string& name, int x, int y, int z );

		/** Set uniform (vec4).
		 * @param name Name of uniform.
		 * @param x x value.
		 * @param y y value.
		 * @param z z value.
		 * @param w w value.
		 * @return true on success.
		 */
		bool set_uniform( const std::string& name, int x, int y, int z, int w );

	private:
		typedef std::map<const std::string, GLint> UniformMap;
		typedef std::vector<GLuint> ShaderArray;

		void delete_program();

		UniformMap m_uniforms;
		ShaderArray m_shaders;
		GLuint m_program;
		bool m_is_linked;
};

}
