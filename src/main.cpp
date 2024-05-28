#include <iostream>
#include <vector>

#include "./includes/glm/gtc/matrix_transform.hpp"

#include "./window.hpp"
#include "./shader.hpp"
#include "./buffer.hpp"
#include "./texture.hpp"

void framebuffer_size_callback(int width, int height);
void process_input(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    GLFWwindow* window = init_window(SCR_WIDTH, SCR_HEIGHT, "openGL");
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Make sure GLAD is initialized.
    Debug::init();

    Shader shader("./src/shaders/triangle.vert", "./src/shaders/triangle.frag");

    std::vector<float> vertices = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
        0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,   // top 
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };  

    std::vector<int> indices {
        0, 1, 2,
        1, 2, 3
    };

    Buffer buffer(vertices, indices, GL_STATIC_DRAW);
    config_vertex_attribute();
    Texture tex("./assets/imgs/clouds.jpg");

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2, 0.3, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        tex.bind();
        shader.use();

        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        shader.set_mat4("model", model);
        shader.set_mat4("view", view);
        shader.set_mat4("projection", projection);

        buffer.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    shader.remove();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}