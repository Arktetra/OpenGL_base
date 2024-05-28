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

void config_vertex_attribute(int attrib_pointer, int size, int stride, void* offset);
void config_vertex_attribute(
    int pos_attrib_pointer = 0,
    int col_attrib_pointer = 1,
    int tex_attrib_pointer = 2,
    int pos_size = 3,
    int col_size = 3,
    int tex_size = 2,
    int stride = 8 * sizeof(float),
    void* pos_offset = (void*)0,
    void* col_offset = (void*)(3 * sizeof(float)),
    void* tex_offset = (void*)(6 * sizeof(float))
);

#endif