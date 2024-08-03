#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <cstdlib>
#include <algorithm>

#include "triangles.hpp"
#include "main_utils.hpp"

namespace Terrain {
    struct Point {
        int x, z;

        void print();
        bool is_equal(Point p);
    };

    class FaultFormation {
        int terrain_size;
        int iterations;
        float min_height;
        float max_height;
        // std::vector<float> height_map;
        ProcGen::HeightMap height_map;
        Triangles triangles;

        public:
            FaultFormation(int terrain_size, int iterations, float min_height, float max_height);
            Point generate_random_point();
            void apply_fault_formation();
            void init_height_map();
            void scale_height_map();
            void render();
    };
}

#endif