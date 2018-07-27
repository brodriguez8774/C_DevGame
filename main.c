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
// Shaders copied from https://learnopengl.com/Getting-started/Hello-Triangle
const char* VERTEX_SHADER_SOURCE = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n\n"
"void main() {\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0 ";
const char* FRAGMENT_SHADER_SOURCE = "#version 330 core\n"
"out vec4 FragColor;\n\n"
"void main() {\n"
"    FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\n\0 ";


// Method Declaration.
unsigned int set_up_shaders(unsigned int);
unsigned int create_vertex_shader(unsigned int);
unsigned int create_fragment_shader(unsigned int);
void render_data(unsigned int);
// Callbacks.
void error_callback(int, const char*);
void key_callback(GLFWwindow*, int, int, int, int);
void framebuffer_size_callback(GLFWwindow*, int, int);



/**
 * Program's main.
 * Initializes and runs program.
 */
int main(int argc, char* argv[]) {
    GLFWwindow* window;                 // The main window object to render on.
    static const GLfloat window_background[] = {0.2f, 0.2f, 0.3f, 1.0f};
    unsigned int shader_program = 0;    // A unique id ref to set of linked shaders to render with.

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

    // Set up rendering shaders.
    shader_program = set_up_shaders(shader_program);

    // Main loop for window rendering.
    while (! glfwWindowShouldClose(window) ) {
        glClearBufferfv(GL_COLOR, 0, window_background);

        render_data(shader_program);

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
 *  Establish shaders to render GPU visuals.
 *  Visuals are processed through shaders in order of:
 *      * Vertex Shaders
 *      * Geometry Shaders
 *      * Fragment Shaders
 *  Note that a basic geometry shader is provided by default, so creating a new one is optional.
 */
unsigned int set_up_shaders(unsigned int shader_program) {
    unsigned int vertex_shader = 0;     // A unique id relating to the vertex shader.
    unsigned int fragment_shader = 0;   // A unique id relating to the fragment shader.

    // Create shaders.
    vertex_shader = create_vertex_shader(vertex_shader);
    fragment_shader = create_fragment_shader(fragment_shader);

    // Link shaders.
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // Delete old references to shaders.
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}


/**
 * Compiles vertex shader.
 */
unsigned int create_vertex_shader(unsigned int vertex_shader) {
    int success;
    char info_log[512];

    // Initialize.
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &VERTEX_SHADER_SOURCE, NULL);
    glCompileShader(vertex_shader);

    // Check for errors.
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (! success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        fprintf(stderr, "Error compiling vertex shader: %s\n", info_log);
    }

    return vertex_shader;
}


/**
 * Compiles fragment shader.
 */
unsigned int create_fragment_shader(unsigned int fragment_shader) {
    int success;
    char info_log[512];

    // Initialize.
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &FRAGMENT_SHADER_SOURCE, NULL);
    glCompileShader(fragment_shader);

    // Check for errors.
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (! success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        fprintf(stderr, "Error compiling fragment shader: %s\n", info_log);
    }

    return fragment_shader;
}


/**
 * Basic example of attempting to render a triangle.
 */
void render_data(unsigned int shader_program) {
    unsigned int vertex_buffer_object;
    unsigned int vertex_array_object;
    float verticies[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    // Generate array object and buffers.
    glGenVertexArrays(1, &vertex_array_object);
    glGenBuffers(1, &vertex_buffer_object);

    // Add vertex data to graphics buffer. Start with array object, then vertex buffers.
    glBindVertexArray(vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    // Set vertix attribute pointers?
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 * sizeof(float)), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Use shader program when rendering.
    glUseProgram(shader_program);

    // Draw object.
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
