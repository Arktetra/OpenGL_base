#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../includes/glm/glm.hpp"

struct CameraParams {
    glm::vec3 pos = glm::vec3(0.0, 0.0, 3.0);
    glm::vec3 front = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

    float sensitivity = 0.1;
    float yaw = -90.0;
    float pitch = 0.0;
};

class Camera {


    public:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    float sensitivity;
    float yaw;
    float pitch;
    bool first_mouse;

    Camera(CameraParams cam_params);
};

#endif