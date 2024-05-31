#include "camera.hpp"

Camera::Camera(CameraParams cam_params) {
    this->pos = cam_params.pos;
    this->front = cam_params.front;
    this->up = cam_params.up;

    this->sensitivity = cam_params.sensitivity;
    this->yaw = cam_params.yaw;
    this->pitch = cam_params.pitch;

    this->first_mouse = true;
}