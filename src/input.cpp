#include "input.hpp";

void process_input(GLFWwindow* window, Camera camera) {
    if (is_pressed(window, Key::ESC)) {
        glfwSetWindowShouldClose(window, true);
    }

    if (is_pressed(window, Key::FRONT)) {
        camera.pos += camera.front * camera.speed;
    }
    if (is_pressed(window, Key::BACK)) {
        camera.pos -= camera.pos * camera.speed;
    }
    if (is_pressed(window, Key::LEFT)) {
        camera.pos -= glm::normalize(glm::cross(camera.front, camera.up)) * camera.speed;
    }
    if (is_pressed(window, Key::RIGHT)) {
        camera.pos += glm::normalize(glm::cross(camera.front, camera.up)) * camera.speed;
    }
}

bool is_pressed(GLFWwindow* window, Key key) {
    switch (key) {
        case Key::FRONT:
            if ((glfwGetKey(window, GLFW_KEY_W)) == GLFW_PRESS) {
                return true;
            }
            break;
        case Key::BACK:
            if ((glfwGetKey(window, GLFW_KEY_S)) == GLFW_PRESS) {
                return true;
            }
            break;
        case Key::LEFT:
            if ((glfwGetKey(window, GLFW_KEY_A)) == GLFW_PRESS) {
                return true;
            }
            break;
        case Key::RIGHT:
            if ((glfwGetKey(window, GLFW_KEY_D)) == GLFW_PRESS) {
                return true;
            }
    }
}