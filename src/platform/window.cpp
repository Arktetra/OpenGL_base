#include "./window.hpp"

/**
 * Construct a new Window:: Window object
 * 
 * #### Parameters
 * winparam (WinParams): parameters for windows. A WinParams struct with default fields: 
 * width (int) = 800, height (int) = 600, title (const char*) = "ProcGen", context (bool) = false.
 * 
 * #### Examples
 * `Window window = Window({.width = 800, .height = 600, .title = "ProcGen", .context = false});`
 * `Window window = Window({.context = true});
 */
Window::Window(WinParams winparam) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ptr = glfwCreateWindow(winparam.width, winparam.height, winparam.title, NULL, NULL);

    if (this->ptr == NULL) {
        std::cout << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwSetFramebufferSizeCallback(this->ptr, framebuffer_size_callback);

    if (winparam.context == true) {
        make_context_current();
    }
} 

void Window::make_context_current() {
    glfwMakeContextCurrent(this->ptr);
}

bool Window::close() {
    return glfwWindowShouldClose(this->ptr);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}



