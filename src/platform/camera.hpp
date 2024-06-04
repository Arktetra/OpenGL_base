#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../includes/glm/glm.hpp"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

struct CameraParams {
    glm::vec3 pos = glm::vec3(0.0, 0.0, 3.0);
    glm::vec3 front = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

    float sensitivity = 0.1;
    float yaw = -90.0;
    float pitch = 0.0;
    float speed = 2.5f;
};

class Camera {


    public:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    float sensitivity;
    float yaw;
    float pitch;
    bool first_mouse;
    float speed;

    Camera(CameraParams cam_params);
    void process_keyboard(CameraMovement direction, float delta_time);
    void process_mouse_movement(float xoffset, float yoffset);
    void update_camera_vectors();
};

#endif