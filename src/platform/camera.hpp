#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

struct CameraParams {
    glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 front = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

    float sensitivity = 0.1;
    float yaw = -90.0;
    float pitch = 0.0;
    float speed = 2.5f;
    float zoom = 45.0;
};

class Camera {


    public:
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    float sensitivity;
    float yaw;
    float pitch;
    bool first_mouse;
    float speed;
    float zoom;

    Camera(CameraParams cam_params);
    void process_keyboard(CameraMovement direction, float delta_time);
    void process_mouse_movement(float xoffset, float yoffset, bool constrain_pitch = true);
    void update_camera_vectors();
    void process_mouse_scroll(float y_offset);
    float get_zoom();
    glm::mat4 get_view_matrix();
};

#endif