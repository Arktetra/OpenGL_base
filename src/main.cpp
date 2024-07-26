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
    .pos = glm::vec3(67.0f, 627.5f, 169.9f), 
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window.ptr, true);
    ImGui_ImplOpenGL3_Init();

    GLint max_tess_level;
    glGetIntegerv(GL_MAX_TESS_GEN_LEVEL, &max_tess_level);
    std::cout << "[INFO] max available tess level: " << max_tess_level << std::endl;

    glEnable(GL_DEPTH_TEST);

    Shader tessHeightMapShader(
        "src/shaders/height.vert", 
        "src/shaders/height.frag",
        "src/shaders/height.tesc", 
        "src/shaders/height.tese"
    );


    // load and create a texture
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("assets/height_maps/iceland.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        GLint id;
        glGetIntegerv(GL_ACTIVE_TEXTURE, &id);
        // std::cout << "uniform height_map location:" <<  glGetUniformLocation(tessHeightMapShader.ID, "height_map") << std::endl;
        std::cout << "uniform height_map location:" <<  glGetUniformLocation(tessHeightMapShader.get_id(), "height_map") << std::endl;
        std::cout << "current active texture: " << id << std::endl;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // tessHeightMapShader.setInt("heightMap", 0);
        tessHeightMapShader.set_int("heightMap", 0);

        std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    std::vector<float> vertices;

    unsigned int rez = 20;
    for (unsigned int i = 0; i <= rez - 1; i++) {
        for (unsigned int j = 0; j <= rez - 1; j++) {
            vertices.push_back(-width / 2.0 + width * i / (float)rez);
            vertices.push_back(0.0);
            vertices.push_back(-height / 2.0 + height * j / (float)rez);
            vertices.push_back(i / (float)rez);
            vertices.push_back(j / (float)rez);

            vertices.push_back(-width / 2.0 + width * (i + 1) / (float)rez);
            vertices.push_back(0.0);
            vertices.push_back(-height / 2.0 + height * j / (float)rez);
            vertices.push_back((i + 1) / (float)rez);
            vertices.push_back(j / (float)rez);

            vertices.push_back(-width / 2.0 + width * i / (float)rez);
            vertices.push_back(0.0);
            vertices.push_back(-height / 2.0 + height * (j + 1) / (float)rez);
            vertices.push_back(i / (float)rez);
            vertices.push_back((j + 1) / (float)rez);
            
            vertices.push_back(-width / 2.0 + width * (i + 1) / (float)rez);
            vertices.push_back(0.0);
            vertices.push_back(-height / 2.0 + height * (j + 1) / (float)rez);
            vertices.push_back((i + 1) / (float)rez);
            vertices.push_back((j + 1) / (float)rez);
        }
    }
    std::cout << "[INFO] loaded " << rez * rez << " patches of 4 control points each" << std::endl;
    std::cout << "[INFO] processing " << rez * rez * 4 << " vertices in vertex shader" << std::endl;

    std::vector<int> indices;

    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 2; k++) {
                indices.push_back(j + width * (i + k));
            }
        }
    }

    // Buffer terrain(vertices, indices, GL_STATIC_DRAW);
    Buffer terrain(vertices, GL_STATIC_DRAW);
    ProcGen::config_vertex_attribute(0, 3, 5 * sizeof(float), (void*)0);
    ProcGen::config_vertex_attribute(1, 2, 5 * sizeof(float), (void*)(sizeof(float) * 3));

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    std::cout << "[INFO] window loop entered." << std::endl;

    while (!window.is_close()) {
        process_input(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // ImGui::ShowDemoWindow();

        float current_frame = static_cast<float>(glfwGetTime());

        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        tessHeightMapShader.use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100000.0f);
        glm::mat4 view = camera.get_view_matrix();
        tessHeightMapShader.set_mat4("projection", projection);
        tessHeightMapShader.set_mat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);

        tessHeightMapShader.set_mat4("model", model);

        terrain.bind();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_PATCHES, 0, rez * rez * 4);

        tool_bar();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window.ptr);
        glfwPollEvents();
    }
    // height_map_shader.remove();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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