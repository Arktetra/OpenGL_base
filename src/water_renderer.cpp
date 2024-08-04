#include "water_renderer.hpp"

Water::Renderer::Renderer(Water::Shader shader, float height) {
    this->shader = shader;

    this->height = height;

    std::vector<float> vertices = {
        -400, height, -400, 
        -400, height, 400,
        400, height, -400,
        400, height, 400
    };

    std::vector<int> indices = {
        0, 1, 2,
        1, 2, 3
    };

    this->VAO = Buffer::create_VAO(vertices, indices, GL_STATIC_DRAW);
    ProcGen::config_vertex_attribute(0, 3, 3 * sizeof(float), (void*)0);
}

void Water::Renderer::prepare_render(Camera camera, glm::mat4 projection) {
    shader.use();
    shader.load_projection_matrix(projection);
    shader.load_view_matrix(camera.get_view_matrix());
    shader.load_model_matrix(glm::mat4(1.0f));
}

void Water::Renderer::render(Camera camera, glm::mat4 projection) {
    prepare_render(camera, projection);
    Buffer::bind(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}