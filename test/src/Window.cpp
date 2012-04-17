#include <GL/glew.h>

#include "Window.hpp"

#include <SFML/Window.hpp>

void init_test_window() {
	static sf::Window window( sf::VideoMode( 50, 50 ), "Unit Test" );

	glewInit();
}
