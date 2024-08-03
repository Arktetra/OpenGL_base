#include "main_utils.hpp"

ProcGen::Point::Point(int x, int z) {
    this->x = x;
    this->z = z;
}

void ProcGen::Point::print() {
    std::cout << "x: " << x << ", z: " << z << std::endl;
}

bool ProcGen::Point::is_equal(Point p) {
    if (this->x == p.x && this->z == p.z) {
        return true;
    } else {
        return false;
    }
}

ProcGen::Point ProcGen::Point::random() {
    int x = rand();
    int z = rand();

    return ProcGen::Point(x, z);
}

ProcGen::Point ProcGen::Point::random(int range) {
    int x = rand() % range;
    int z = rand() % range;

    return ProcGen::Point(x, z);
}

ProcGen::Point ProcGen::Point::random(int x_range, int z_range) {
    int x = rand() % x_range;
    int z = rand() % z_range;

    return ProcGen::Point(x, z);
}

// ----------------------------------------------------------

void ProcGen::HeightMap::init_height_map() {
    for (int z = 0; z < this->depth; z++) {
        for (int x = 0; x < this->width; x++) {
            this->values.push_back(0.0);
        }
    }
}

ProcGen::HeightMap::HeightMap(int width, int depth) {
    this->width = width;
    this->depth = depth;

    init_height_map();
}

ProcGen::HeightMap::HeightMap(int size) {
    this->width = size;
    this->depth = size;

    init_height_map();
}

int ProcGen::HeightMap::get_width() {
    return this->width;
}

int ProcGen::HeightMap::get_depth() {
    return this->depth;
}

float ProcGen::HeightMap::get_value(int x, int z) {
    return this->values[z * depth + x];
}

float ProcGen::HeightMap::get_value(Point p) {
    return this->values[p.z * depth + p.x];
}

void ProcGen::HeightMap::set_value(int x, int z, float value) {
    this->values[z * depth + x] = value;
}

void ProcGen::HeightMap::set_value(Point p, float value) {
    this->values[p.z * depth + p.x] = value;
}

void ProcGen::HeightMap::normalize(float min_height, float max_height) {
    float min = *std::min_element(values.begin(), values.end());
    float max = *std::max_element(values.begin(), values.end());

    if (max <= min) { 
        std::cout << "[INFO] cannot normalize" << std::endl;
        return;
    }

    float curr_delta_height = max - min;
    float new_delta_height = max_height - min_height;

    for (int i = 0; i < width * depth; i++) {
        this->values[i] = (this->values[i] - min) / curr_delta_height * new_delta_height;
    }
}

void ProcGen::HeightMap::print(int range) {
    for (int z = 0; z < range; z++) {
        for (int x = 0; x < range; x++) {
            std::cout << get_value(x, z) << " ";
        }
        std::cout << std::endl;
    }
}