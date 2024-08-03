#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "../includes/GLAD/glad.h"

#include <iostream>

class Texture {
    unsigned int id;

    public:
    Texture() {}
    Texture(const char* texture_path);
    void bind();
    unsigned get_id();
};

#endif