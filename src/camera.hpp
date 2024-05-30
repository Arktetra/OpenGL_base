#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "includes/glm/glm.hpp"

class Camera {

    public:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    float speed;
};

#endif