#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "./utils.hpp"

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* TITLED = "ProcGen";

class Window {

    public: 
    GLFWwindow* ptr;
    Window(int width = SCR_WIDTH, int height = SCR_HEIGHT, const char* title = "ProcGen");
};

#endif