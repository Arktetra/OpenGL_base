#include <iostream>
#include <vector>

#include "./includes/glm/gtc/matrix_transform.hpp"

#include "platform/window.hpp"
#include "platform/shader.hpp"
#include "platform/buffer.hpp"
#include "platform/texture.hpp"
#include "platform/camera.hpp"

void process_input(Window window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Camera camera = Camera({});

float last_x;
float last_y;

float delta_time = 0.0f;
float last_frame = 0.0f;

int main() {
    Window window = Window({.context = true, .disable_cursor = true});
    glfwSetCursorPosCallback(window.ptr, mouse_callback);

    ProcGen::init();

    Shader shader("./src/shaders/triangle.vert", "./src/shaders/triangle.frag");

    std::vector<float> vertices = {
        // positions         // colors
        2.0f, -2.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,   // bottom right
        -2.0f, -2.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
        2.0f,  2.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,   // top 
        -2.0f, 2.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };  

    std::vector<int> indices {
        0, 1, 2,
        1, 2, 3
    };

    Buffer buffer(vertices, indices, GL_STATIC_DRAW);
    ProcGen::config_vertex_attribute();
    Texture tex("./assets/imgs/clouds.jpg");

    while (!window.is_close()) {
        process_input(window);

        float current_frame = static_cast<float>(glfwGetTime());
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        tex.bind();
        shader.use();

        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        view = glm::lookAt(camera.pos, camera.front + camera.pos, camera.up);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        shader.set_mat4("model", model);
        shader.set_mat4("view", view);
        shader.set_mat4("projection", projection);

        buffer.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();
    }
    shader.remove();

    glfwTerminate();
    return 0;
}

void process_input(Window window) {
    if (window.is_pressed(Key::ESC) == true) { window.close(); }

    if (window.is_pressed(Key::W))
        camera.process_keyboard(CameraMovement::FORWARD, delta_time);
    if (window.is_pressed(Key::S))
        camera.process_keyboard(CameraMovement::BACKWARD, delta_time);
    if (window.is_pressed(Key::A))
        camera.process_keyboard(CameraMovement::LEFT, delta_time);
    if (window.is_pressed(Key::D))
        camera.process_keyboard(CameraMovement::RIGHT, delta_time);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (camera.first_mouse) {
        last_x = xpos; last_y = ypos;
        camera.first_mouse = false;
    }

    float xoffset = xpos - last_x;
    float yoffset = last_y - ypos;

    last_x = xpos;
    last_y = ypos;

    camera.process_mouse_movement(xoffset, yoffset);
    
}