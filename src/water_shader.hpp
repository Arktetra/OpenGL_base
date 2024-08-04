#ifndef WATER_SHADER_HPP
#define WATER_SHADER_HPP

#include "platform/shader.hpp"

namespace Water {
    class Shader : public OpenGLBase::Shader {
        public:
            Shader() : OpenGLBase::Shader() {}
            Shader(
                const char* vert_path,
                const char* frag_path
            ) : OpenGLBase::Shader(vert_path, frag_path) {}

            void load_projection_matrix(glm::mat4 projection) {
                set_mat4("projection", projection);
            }

            void load_view_matrix(glm::mat4 view) {
                set_mat4("view", view);
            }

            void load_model_matrix(glm::mat4 model) {
                set_mat4("model", model);
            }
    };
}



#endif