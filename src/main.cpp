#include <iostream>
#include <vector>

#include "./includes/glm/gtc/matrix_transform.hpp"
#include "includes/stb_image.h"

#include "platform/window.hpp"
#include "platform/shader.hpp"
#include "platform/buffer.hpp"
#include "platform/texture.hpp"
#include "platform/camera.hpp"

void process_input(Window window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers);

// settings
int use_wireframe = 0;
int display_grayscale = 0;

// Camera camera = Camera({});

Camera camera = Camera({
    .pos = glm::vec3(67.0f, 627.5f, 169.9f), 
    .up = glm::vec3(0.0f, 1.0f, 0.0f),
    .speed = 128.0f
});

float last_x;
float last_y;

float delta_time = 0.0f;
float last_frame = 0.0f;

glm::vec3 light_pos(1.2, 1.0, 2.0);

int main() {
    Window window = Window({.context = true, .disable_cursor = true});
    glfwSetCursorPosCallback(window.ptr, mouse_callback);
    glfwSetKeyCallback(window.ptr, key_callback);

    ProcGen::init();

    glEnable(GL_DEPTH_TEST);

    Shader height_map_shader("src/shaders/height_map.vert", "src/shaders/height_map.frag");

    stbi_set_flip_vertically_on_load(true);
    int width, height, n_channels;
    unsigned char* data = stbi_load(
        "assets/imgs/clouds.jpg",
        &width,
        &height,
        &n_channels,
        0
    );

    if (data) {
        std::cout << "Height map size: " << height << " x " << width << std::endl;
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    std::vector<float> vertices;
    float y_scale = 64.0f / 256.0f, y_shift = 16.0f;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char* texel = data + (j + width * i) * n_channels;

            unsigned char y = texel[0];

            vertices.push_back(-height / 2.0f + height * i / (float)height);        // v.z
            vertices.push_back((int)y * y_scale - y_shift);  // v.y
            vertices.push_back(-width / 2.0f + width * j / (float)width);         // v.x
        }
    }

    stbi_image_free(data);

    std::vector<int> indices;

    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 2; k++) {
                indices.push_back(j + width * (i + k));
            }
        }
    }

    const unsigned int NUM_STRIPS = height - 1;
    const unsigned int NUM_VERTS_PER_STRIP = width * 2;

    Buffer terrain(vertices, indices, GL_STATIC_DRAW);
    ProcGen::config_vertex_attribute(0, 3, 3 * sizeof(float), (void*)0);

    while (!window.is_close()) {
        process_input(window);

        float current_frame = static_cast<float>(glfwGetTime());

        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        height_map_shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
        glm::mat4 view = glm::lookAt(camera.pos, camera.front + camera.pos, camera.up);
        height_map_shader.set_mat4("projection", projection);
        height_map_shader.set_mat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        height_map_shader.set_mat4("model", model);

        terrain.bind();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for (unsigned int strip = 0; strip < NUM_STRIPS; strip++) {
            glDrawElements(
                GL_TRIANGLE_STRIP,
                NUM_VERTS_PER_STRIP,
                GL_UNSIGNED_INT,
                (void*)(sizeof(unsigned int) * (NUM_VERTS_PER_STRIP) * strip)
            );
        }

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();
    }
    height_map_shader.remove();

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers) {
    if (action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_SPACE:
                use_wireframe = 1 - use_wireframe;
                break;
            case GLFW_KEY_G:
                display_grayscale = 1 - display_grayscale;
                break;
            default:
                break;
        }
    }
}