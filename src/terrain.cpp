#include "terrain.hpp"

void Terrain::Base::render() {
    triangles.render();
}

// ----------------------------------------------------------------------------------------------------------------

Terrain::FaultFormation::FaultFormation(int terrain_size, int iterations, float min_height, float max_height) {
    std::cout << "[INFO] starting fault formation algorithm." << std::endl;

    this->terrain_size = terrain_size;
    this->iterations = iterations;
    this->min_height = min_height;
    this->max_height = max_height;

    height_map = ProcGen::HeightMap(terrain_size);

    std::cout << "[INFO] applying fault formation." << std::endl;
    Terrain::FaultFormation::apply_fault_formation();
    std::cout << "[INFO] finished applying fault formation." << std::endl;

    apply_filters(0.5, 1);

    height_map.normalize(min_height, max_height);

    triangles = Triangles(terrain_size, terrain_size, height_map);
}

void Terrain::FaultFormation::apply_fault_formation() {
    float delta_height = this->max_height - this->min_height;

    std::cout << "[INFO] performing fault formation for " << this->iterations << " iterations." << std::endl;

    for (int current_iter = 0; current_iter < this->iterations; current_iter++) {
        float iteration_ratio = (float) current_iter / (float) iterations;
        float height = max_height - iteration_ratio * delta_height;

        ProcGen::Point a = ProcGen::Point::random(this->terrain_size);
        ProcGen::Point b = ProcGen::Point::random(this->terrain_size);

        while (a.is_equal(b)) {
            b = ProcGen::Point::random(this->terrain_size);
        }

        for (int z = 0; z < this->terrain_size; z++) {
            for (int x = 0; x < this->terrain_size; x++) {
                float cross_product = (x - a.x) * (b.z - a.z) - (b.x - a.x) * (z - a.z);

                if (cross_product > 0) {
                    float current_height = this->height_map.get_value(x, z);
                    this->height_map.set_value(x, z, current_height + height);
                }
            }
        }
    }
}

void Terrain::FaultFormation::apply_filters(float filter_coefficient, int reps) {
    std::cout << "[INFO] applying finite impulse response filter." << std::endl;

    Filters::FIR FIR_filter(height_map, filter_coefficient);

    for (int i = 0; i < reps; i++) {
        FIR_filter.apply_left_to_right();
        FIR_filter.apply_bottom_to_top();
        FIR_filter.apply_right_to_left();
        FIR_filter.apply_top_to_bottom();
    }
}