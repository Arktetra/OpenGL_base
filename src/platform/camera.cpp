#include "camera.hpp"

Camera::Camera(CameraParams cam_params) {
    this->pos = cam_params.pos;
    this->front = cam_params.front;
    this->up = cam_params.up;

    this->sensitivity = cam_params.sensitivity;
    this->yaw = cam_params.yaw;
    this->pitch = cam_params.pitch;

    this->first_mouse = true;
    this->speed = cam_params.speed;
}

void Camera::process_keyboard(CameraMovement direction, float delta_time) {
    float velocity = this->speed * delta_time;
    if (direction == CameraMovement::FORWARD)
        this->pos += this->front * velocity;
    if (direction == CameraMovement::BACKWARD)
        this->pos -= this->front * velocity;
    if (direction == CameraMovement::LEFT)
        this->pos -= this->right * velocity;
    if (direction == CameraMovement::RIGHT)
        this->pos += this->right * velocity;
    
    update_camera_vectors();
}

void Camera::process_mouse_movement(float xoffset, float yoffset) {
    xoffset *= this->sensitivity;
    yoffset *= this->sensitivity;

    this->yaw += xoffset;
    this->pitch += yoffset;

    if (this->pitch > 89.0f) {
        this->pitch = 89.0f;
    }
    if (this->pitch < -89.0f) {
        this->pitch = -89.0f;
    }

    update_camera_vectors();
}

void Camera::update_camera_vectors() {
    this->front = glm::normalize(glm::vec3(
        cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
        sin(glm::radians(this->pitch)),
        sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))
    ));
    this->right = glm::normalize(glm::cross(this->front, this->up));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}