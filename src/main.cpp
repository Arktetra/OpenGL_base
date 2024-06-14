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

glm::vec3 light_pos(1.2, 1.0, 2.0);

int main() {
    Window window = Window({.context = true, .disable_cursor = true});
    glfwSetCursorPosCallback(window.ptr, mouse_callback);

    ProcGen::init();

    glEnable(GL_DEPTH_TEST);

    // Shader shader("./src/shaders/triangle.vert", "./src/shaders/triangle.frag");
    Shader cube_shader("./src/shaders/cube_object.vert", "./src/shaders/cube_object.frag");
    Shader source_shader("./src/shaders/source.vert", "./src/shaders/source.frag");

    // std::vector<float> vertices = {
    //     // positions         // colors
    //     2.0f, -2.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,   // bottom right
    //     -2.0f, -2.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
    //     2.0f,  2.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,   // top 
    //     -2.0f, 2.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    // };  

    // std::vector<int> indices {
    //     0, 1, 2,
    //     1, 2, 3
    // };

    std::vector<float> vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };


    // Buffer buffer(vertices, indices, GL_STATIC_DRAW);
    // ProcGen::config_vertex_attribute();

    Buffer object(vertices, GL_STATIC_DRAW);
    ProcGen::config_vertex_attribute(0, 3, 6 * sizeof(float), (void*)0);
    ProcGen::config_vertex_attribute(1, 3, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    Buffer source(vertices, GL_STATIC_DRAW);
    ProcGen::config_vertex_attribute(0, 3, 6 * sizeof(float), (void*)0);
    Texture tex("./assets/imgs/clouds.jpg");

    while (!window.is_close()) {
        process_input(window);

        float current_frame = static_cast<float>(glfwGetTime());
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glClearColor(0.1, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        light_pos.x = glm::sin(glfwGetTime());
        light_pos.y = glm::cos(glfwGetTime());
        light_pos.z = 0;

        // tex.bind();
        cube_shader.use();
        cube_shader.set_vec3("object_color", 1.0, 0.5, 0.31);
        cube_shader.set_vec3("light_color", 1.0f, 1.0f, 1.0f);
        cube_shader.set_vec3("light_pos", light_pos);
        cube_shader.set_vec3("view_pos", camera.pos);

        // create transformations
        // view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 view = glm::lookAt(camera.pos, camera.front + camera.pos, camera.up);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 model = glm::mat4(1.0);

        cube_shader.set_mat4("projection", projection);
        cube_shader.set_mat4("view", view);
        cube_shader.set_mat4("model", model);

        object.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        source_shader.use();
        source_shader.set_mat4("projection", projection);
        source_shader.set_mat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, light_pos);
        model = glm::scale(model, glm::vec3(0.2));     // smaller cube
        source_shader.set_mat4("model", model);

        source.bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();
    }
    cube_shader.remove();
    source_shader.remove();

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