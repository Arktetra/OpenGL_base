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
        
        if (winparam.disable_cursor == true) {
            glfwSetInputMode(this->ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
} 

void Window::make_context_current() {
    glfwMakeContextCurrent(this->ptr);
}

bool Window::is_pressed(Key key) {
    if (glfwGetKey(this->ptr, key) == GLFW_PRESS) {
        return true;
    } else {
        return false;
    }
}

bool Window::is_close() {
    return glfwWindowShouldClose(this->ptr);
}

void Window::close() {
    glfwSetWindowShouldClose(this->ptr, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}



