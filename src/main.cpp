#include <iostream>
#include <vector>

#include "./includes/glm/gtc/matrix_transform.hpp"
#include "includes/stb_image.h"

#include "includes/imgui/imgui.h"
#include "includes/imgui/backends/imgui_impl_glfw.h"
#include "includes/imgui/backends/imgui_impl_opengl3.h"


#include "platform/window.hpp"
#include "platform/shader.hpp"
#include "platform/buffer.hpp"
#include "platform/texture.hpp"
#include "platform/camera.hpp"
#include "perm.hpp"
// #include "triangles.hpp"
#include "terrain.hpp"
#include "texture_generator.hpp"

void process_input(Window window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void tool_bar();

// settings

int use_wireframe = 0;
int display_grayscale = 0;

// Camera camera = Camera({});

Camera camera = Camera({
    .pos = glm::vec3(67.0f, 300.f, 169.9f), 
    .up = glm::vec3(0.0f, 1.0f, 0.0f),
    .yaw = -128.1f,
    .pitch = -42.4f,
    .speed = 50.0f
});

float last_x;
float last_y;

float delta_time = 0.0f;
float last_frame = 0.0f;

glm::vec3 light_pos(1.2, 1.0, 2.0);

int main() {
    Window window = Window({.context = true, .disable_cursor = true});
    glfwSetKeyCallback(window.ptr, key_callback);
    glfwSetCursorPosCallback(window.ptr, mouse_callback);
    glfwSetScrollCallback(window.ptr, scroll_callback);
    
    glfwSetInputMode(window.ptr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    ProcGen::init();

    Shader triangles_shader(
        "src/shaders/terrain.vert",
        "src/shaders/terrain.frag"
    );

    Terrain::FaultFormation terrain(800, 100, 0, 255);

    std::vector<const char*> paths = {
        "assets/imgs/sand.jpg",
        "assets/imgs/grass_land.jpg",
        "assets/imgs/snow.jpg"
    };

    TexturePack textures(paths);

    // Texture texture0("assets/imgs/sand.jpg");
    // Texture texture1("assets/imgs/grass_land.jpg");
    // Texture texture2("assets/imgs/snow.jpg");

    // std::cout << texture0.get_id() << texture1.get_id() << std::endl;

    triangles_shader.use();
    triangles_shader.set_int("texture0", 0);
    triangles_shader.set_int("texture1", 1);
    triangles_shader.set_int("texture2", 2);

    // std::cout << GL_TEXTURE0 << " " << GL_TEXTURE1 << std::endl;

    // return 0;

    


    while (!window.is_close()) {
        process_input(window);

        float current_frame = static_cast<float>(glfwGetTime());

        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glClearColor(0.1, 0.1, 0.1, 0.1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        triangles_shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100000.0f);
        glm::mat4 view = camera.get_view_matrix();
        triangles_shader.set_mat4("projection", projection);
        triangles_shader.set_mat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);

        triangles_shader.set_mat4("model", model);

        // glActiveTexture(GL_TEXTURE0);
        // texture0.bind();
        // glActiveTexture(GL_TEXTURE1);
        // texture1.bind();
        // glActiveTexture(GL_TEXTURE2);
        // texture2.bind();

        textures.bind();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        terrain.render();

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();
    }

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

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.process_mouse_scroll(yoffset);
}

void tool_bar() {
    bool tool_active = true;
    char buf[255];
    float f;
    ImGui::Begin("Tool", &tool_active, ImGuiWindowFlags_MenuBar);
    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::End();
}