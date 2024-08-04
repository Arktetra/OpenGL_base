#ifndef WATER_RENDERER_HPP
#define WATER_RENDERER_HPP

#include "water_shader.hpp"
#include "platform/buffer.hpp"
#include "platform/camera.hpp"
#include "platform/utils.hpp"

namespace Water {
    class Renderer {
        Water::Shader shader;

        float height;
        unsigned int VAO;

        public:
            Renderer(Water::Shader shader, float height);
            void prepare_render(Camera camera, glm::mat4 projection);
            void render(Camera camera, glm::mat4 projection);
    };
}

#endif 