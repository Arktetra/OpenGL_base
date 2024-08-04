#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <cstdlib>
#include <algorithm>

#include "platform/texture.hpp"
#include "platform/camera.hpp"
#include "triangles.hpp"
#include "main_utils.hpp"
#include "filters.hpp"
#include "terrain_shader.hpp"

namespace Terrain {
    class Base {
        protected:
            int terrain_size;
            float min_height;
            float max_height;
            ProcGen::HeightMap height_map;
            Triangles triangles;

        public:
            Base() {}
            void prepare_render(Terrain::Shader shader, Camera camera, glm::mat4 projection);
            void render(Terrain::Shader shader, Camera camera, glm::mat4 projection);
    };


    class FaultFormation : public Base{
        int iterations;

        public:
            FaultFormation(int terrain_size, int iterations, float min_height, float max_height);
            void apply_fault_formation();
            void apply_filters(float filter_coefficient = 0.5, int reps = 1);
    };
}

#endif