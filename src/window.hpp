#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "./includes/GLFW/glfw3.h"

#include <iostream>

GLFWwindow* init_window(int width, int height, const char* title);

#endif