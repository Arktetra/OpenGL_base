#include "filters.hpp"

Filters::FIR::FIR(ProcGen::HeightMap& height_map, float filter_coefficient) {
    this->height_map = &height_map;
    this->filter_coefficient = filter_coefficient;
}

float Filters::FIR::apply(
    int x, int z, 
    float prev_value
) {
    float current_value = height_map->get_value(x, z);

    float new_value = filter_coefficient * current_value + (1 - filter_coefficient) * prev_value;

    height_map->set_value(x, z, new_value);

    return new_value;
}

void Filters::FIR::apply_left_to_right() {
    float prev_value;

    for (int z = 0, depth = height_map->get_depth(); z < depth; z++) {
        prev_value = height_map->get_value(0, z);

        for (int x = 1, width = height_map->get_depth(); x < width; x++) {
            prev_value = Filters::FIR::apply(x, z, prev_value);
        }
    }
}

void Filters::FIR::apply_right_to_left() {
    float prev_value;

    for (int z = 0, depth = height_map->get_depth(); z < depth; z++) {
        prev_value = height_map->get_value(height_map->get_width() - 1, z);

        for (int x = height_map->get_width() - 2; x >= 0; x--) {
            prev_value = Filters::FIR::apply(x, z, prev_value);
        }
    }
}

void Filters::FIR::apply_bottom_to_top() {
    float prev_value;

    for (int x = 0, width = height_map->get_width(); x < width; x++) {
        prev_value = height_map->get_value(x, 0);

        for (int z = 1, depth = height_map->get_depth(); z < depth; z++) {
            prev_value = Filters::FIR::apply(x, z, prev_value);
        }
    }
}

void Filters::FIR::apply_top_to_bottom() {
    float prev_value;

    for (int x = 0, width = height_map->get_width(); x < width; x++) {
        prev_value = height_map->get_value(x, height_map->get_depth() - 1);

        for (int z = height_map->get_depth() - 2; z >= 0; z--) {
            prev_value = Filters::FIR::apply(x, z, prev_value);
        }
    }
}