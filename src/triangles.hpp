#ifndef TRIANGLES_HPP
#define TRIANGLES_HPP

#include <vector>
#include <iostream>

#include "platform/buffer.hpp"
#include "main_utils.hpp"

class Triangles {
    int width;
    int depth;
    unsigned int triangle_VAO;

    public:
        Triangles() {}
        Triangles(int width, int depth, ProcGen::HeightMap height_map);
        ~Triangles();
        void render();
};

#endif