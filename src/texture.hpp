#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "./includes/GLAD/glad.h"

#include <iostream>

class Texture {
    unsigned int texture;

    public:
    Texture(const char* texture_path);
    void bind();
};

#endif