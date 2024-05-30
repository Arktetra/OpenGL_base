#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "./utils.hpp"

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

struct WinParams {
    int width = 800;
    int height = 600;
    const char* title = "ProcGen";
    bool context = false;
};

class Window {

    public: 
    GLFWwindow* ptr;
    Window(WinParams winparam);
    void make_context_current();
    bool close();
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

#endif