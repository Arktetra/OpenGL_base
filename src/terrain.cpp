#include "terrain.hpp"

void Terrain::Point::print() {
    std::cout << "x: " << this->x << ", y: " << this->z << std::endl;
}

bool Terrain::Point::is_equal(Point p) {
    if (this->x == p.x && this->z == p.z) {
        return true;
    } else {
        return false;
    }
}

Terrain::FaultFormation::FaultFormation(int terrain_size, int iterations, float min_height, float max_height) {
    std::cout << "[INFO] starting fault formation algorithm." << std::endl;

    this->terrain_size = terrain_size;
    this->iterations = iterations;
    this->min_height = min_height;
    this->max_height = max_height;

    // Terrain::FaultFormation::init_height_map();
    height_map = ProcGen::HeightMap(terrain_size);

    std::cout << "[INFO] applying fault formation." << std::endl;
    Terrain::FaultFormation::apply_fault_formation();
    std::cout << "[INFO] finished applying fault formation." << std::endl;

    // Terrain::FaultFormation::scale_height_map();
    height_map.normalize(min_height, max_height);

    triangles = Triangles(terrain_size, terrain_size, height_map);
}

// void Terrain::FaultFormation::init_height_map() {
//     for (int z = 0; z < terrain_size; z++) {
//         for (int x = 0; x < terrain_size; x++) {
//             this->height_map.push_back(0.0);
//         }
//     }
// }

Terrain::Point Terrain::FaultFormation::generate_random_point() {
    int x = rand() % this->terrain_size;
    int z = rand() % this->terrain_size;

    return Terrain::Point {.x = x, .z = z};
}

void Terrain::FaultFormation::apply_fault_formation() {
    float delta_height = this->max_height - this->min_height;

    std::cout << "[INFO] performing fault formation for " << this->iterations << " iterations." << std::endl;

    for (int current_iter = 0; current_iter < this->iterations; current_iter++) {
        float iteration_ratio = (float) current_iter / (float) iterations;
        float height = max_height - iteration_ratio * delta_height;

        Terrain::Point a = generate_random_point();
        Terrain::Point b = generate_random_point();

        while (a.is_equal(b)) {
            b = generate_random_point();
        }

        for (int z = 0; z < this->terrain_size; z++) {
            for (int x = 0; x < this->terrain_size; x++) {
                float cross_product = (x - a.x) * (b.z - a.z) - (b.x - a.x) * (z - a.z);

                if (cross_product > 0) {
                    // float current_height = this->height_map[z * terrain_size + x];
                    // this->height_map[z * terrain_size + x] = current_height + height;
                    float current_height = this->height_map.get_value(x, z);
                    this->height_map.set_value(x, z, current_height + height);
                }
            }
        }
    }
}

// void Terrain::FaultFormation::scale_height_map() {
//     float min = *std::min_element(height_map.begin(), height_map.end());
//     float max = *std::max_element(height_map.begin(), height_map.end());

//     if (max <= min) { return; }

//     float delta_current = max - min;
//     float delta_new = this->max_height - this->min_height;

//     for (int i = 0; i < terrain_size * terrain_size; i++) {
//         this->height_map[i] = (this->height_map[i] - min) / delta_current * delta_new + min_height;
//     }
// }

void Terrain::FaultFormation::render() {
    triangles.render();
}

