#ifndef INPUT_HPP
#define INPUT_HPP

#include "./includes/GLFW/glfw3.h"
#include "camera.hpp"

enum Key {
    FRONT,
    BACK,
    LEFT,
    RIGHT,
    ESC
};

void process_input(GLFWwindow* window);
bool is_pressed(GLFWwindow* window, Key key);


#endif