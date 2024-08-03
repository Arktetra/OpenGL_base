#ifndef FILTERS_HPP
#define FILTERS_HPP

#include <vector>

#include "main_utils.hpp"

namespace Filters {
    class FIR {
        float filter_coefficient;
        ProcGen::HeightMap* height_map;

        public:
            FIR(ProcGen::HeightMap& height_map, float filter_coefficient);
            float apply(int x, int z, float prev_values);
            void apply_left_to_right();
            void apply_right_to_left();
            void apply_top_to_bottom();
            void apply_bottom_to_top();
            void change_filter_order(int new_filter_order);
            int get_filter_order();
    };
}

#endif