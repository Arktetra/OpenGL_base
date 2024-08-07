#include "triangles.hpp"
#include <iostream>
#include "platform/utils.hpp"

Triangles::Triangles(int width, int depth, ProcGen::HeightMap height_map) {
    std::vector<float> vertices;

    for (int z = -depth / 2; z < depth / 2; z++) {
        for (int x = -width / 2; x < width / 2; x++) {
            vertices.push_back(x);
            // vertices.push_back(height_map[(z + depth / 2) * depth + (x + width / 2)]);
            vertices.push_back(height_map.get_value(x + width / 2, z + depth / 2));
            vertices.push_back(z);
            vertices.push_back(x / width);
            vertices.push_back(z / depth);
        }
    }

    std::vector<int> indices;

    for (int z = 0; z < depth - 1; z++) {
        for (int x = 0; x < width - 1; x++) {
            int index_00 = z       * width +  x;
            int index_01 = z       * width + (x + 1);
            int index_10 = (z + 1) * width +  x;
            int index_11 = (z + 1) * width + (x + 1);

            indices.push_back(index_00);
            indices.push_back(index_01);
            indices.push_back(index_10);

            indices.push_back(index_01);
            indices.push_back(index_10);
            indices.push_back(index_11);
        }
    } 

    this->num_indices = indices.size();

    this->triangle_VAO = Buffer::create_VAO(vertices, indices, GL_STATIC_DRAW);

    std::cout << "[INFO] created a mesh with VAO: " << this->triangle_VAO << std::endl;

    ProcGen::config_vertex_attribute(0, 3, 5 * sizeof(float), (void*)0);
    ProcGen::config_vertex_attribute(1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));
}

Triangles::Triangles(int width, int depth, float height) {

    std::vector<float> vertices = {
        -(float)width / 2,      height,    -(float) depth / 2,
        -(float)width / 2,      height,     (float)depth / 2 - 1, 
        (float)width / 2,       height,    -(float)depth / 2,
        (float)width / 2 - 1,   height,     (float)depth / 2 - 1
    };

    std::vector<int> indices = {
        0, 1, 2,
        1, 2, 3
    };

    this->num_indices = indices.size();

    this->triangle_VAO = Buffer::create_VAO(vertices, indices, GL_STATIC_DRAW);

    std::cout << "[INFO] created a quad with VAO: " << this->triangle_VAO << std::endl;

    ProcGen::config_vertex_attribute(0, 3, 3 * sizeof(float), (void*)0);
}

void Triangles::render() {
    Buffer::bind(triangle_VAO);
    glDrawElements(GL_TRIANGLES, this->num_indices, GL_UNSIGNED_INT, NULL);
}

Triangles::~Triangles() {

}

// -------------------------------------------------------------------------