#ifndef UTILS_HPP
#define UTILS_HPP

#include "./includes/GLAD/glad.h"
#include "./includes/GLFW/glfw3.h"

#include <iostream>

namespace Debug {
    void init();
    
    void APIENTRY output(
        GLenum source, 
        GLenum type, 
        unsigned int id, 
        GLenum severity, 
        GLsizei length, 
        const char *message, 
        const void *user_param
    );
};

#endif