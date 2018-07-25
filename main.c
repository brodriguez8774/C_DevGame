/**
 * Brandon Rodriguez
 * DevGame
 *
 * Just a side project to see if I can figure out how to create a very very basic game.
 * Will attempt to include very rudimentary graphics rendering, movement, (probably flat) world, physics, etc.
 */


/**
 * Description:
 *  The starting point for the program.
 */


/**
 * Known Issues:
 *
 */


// Import headers.
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// OpenGL Headers.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;


// Constant Defines.


// Variable Declaration.


// Method Declaration.


/**
 * Program's main.
 * Initializes and runs program.
 */
int main(int argc, char* argv[]) {
    printf("Hello World!\n");

    // Initialize GLFW.
    glewExperimental = true;
    if ( !glfwInit() ) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        exit(1);
    }
}
