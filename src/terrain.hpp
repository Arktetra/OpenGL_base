#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <cstdlib>
#include <algorithm>

#include "platform/texture.hpp"
#include "triangles.hpp"
#include "main_utils.hpp"
#include "filters.hpp"

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
            void render();
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