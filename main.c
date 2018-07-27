/**
 * Brandon Rodriguez
 * DevGame
 */


/**
 * Description:
 *  Just a side project to see if I can figure out how to create a very very basic game.
 *  Will attempt to include very rudimentary graphics rendering, movement, (probably flat) world, physics, etc.
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
#include <GL/glu.h>
#include <GLFW/glfw3.h>
// // #include <glm/glm.hpp>
// // using namespace glm;


// Constant Defines.


// Variable Declaration.


// Method Declaration.
void error_callback(int error, const char* err_description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow*, int width, int height);


/**
 * Program's main.
 * Initializes and runs program.
 */
int main(int argc, char* argv[]) {
    GLFWwindow* window;
    static const GLfloat window_background[] = {0.0f, 0.0f, 0.0f, 1.0f};

    printf("\nStarting program.\n");

    // Set general error output handling.
    glfwSetErrorCallback(error_callback);

    // Initialize glfw.
    if ( !glfwInit() ) {
        exit(EXIT_FAILURE);
    }

    // Initialize OpenGL settings.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Explicitly set OpenGL version.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 4);                // Set antialiasing to 4x.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // Ensure we done use old OpenGL libraries.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    // Value necessary for Mac computers.

    // Attempt to create window.
    printf("Initializing graphics window.\n");
    window = glfwCreateWindow(800, 600, "DevGame", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Set window context and exit settings.
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Check that window initialized fully?
    glewExperimental=GL_TRUE;
    GLenum status = glewInit();
    if( status != GLEW_OK ) {
        fprintf(stderr, "Failed to initialize GLFW: %d\n", status);
        glfwTerminate();
        exit(1);
    }

    // Main loop for window rendering.
    while (! glfwWindowShouldClose(window) ) {
        glClearBufferfv(GL_COLOR, 0, window_background);

        // Clear buffer for new render

        // Check/call events and swap buffers.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate program.
    printf("Terminating program.\n\n");
    glfwDestroyWindow(window);
    glfwTerminate();

    exit(0);
}


/**
 * Generic error handling display for OpenGL library.
 */
void error_callback(int error, const char* err_description) {
    fprintf(stderr, "%s\n", err_description);
}


/**
 * Defines which key presses will close graphics window.
 * Currently set to esc key.
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS)) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


/**
 *  Tells window rendering how to handle resizing.
 */
void framebuffer_size_callback(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}
