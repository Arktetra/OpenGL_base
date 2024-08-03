#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

namespace ProcGen {
    struct Point {
        int x, z;

        Point(int x, int z);
        void print();
        bool is_equal(Point p);

        static Point random();
        static Point random(int range);
    };

    class HeightMap {
        std::vector<float> values;
        int width, depth;

        void init_height_map();

        public:
            HeightMap() {}
            HeightMap(int width, int depth);
            HeightMap(int size);
            int get_width();
            int get_depth();
            float get_value(int x, int z);
            float get_value(Point p);
            void set_value(int x, int z, float value);
            void set_value(Point p, float value);
            void normalize(float min_height, float max_height);
    };
}

#endif