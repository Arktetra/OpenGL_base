#ifndef TERRAIN_SHADER_HPP
#define TERRAIN_SHADER_HPP

#include "platform/shader.hpp"

namespace Terrain {
    class Shader : public OpenGLBase::Shader {
        public:
            Shader() : OpenGLBase::Shader() {}
            Shader(
                const char* vert_path,
                const char* frag_path, 
                const char* tesc_path = nullptr,
                const char* tese_path = nullptr
            ) : OpenGLBase::Shader(vert_path, frag_path, tesc_path, tese_path) {}

            void load_projection_matrix(glm::mat4 projection) {
                set_mat4("projection", projection);
            }

            void load_view_matrix(glm::mat4 view) {
                set_mat4("view", view);
            }

            void load_model_matrix(glm::mat4 model) {
                set_mat4("model", model);
            }

            void set_textures() {
                use();
                set_texture0();
                set_texture1();
                set_texture2();
            }

            void set_texture0() {
                set_int("texture0", 0);
            }

            void set_texture1() {
                set_int("texture1", 1);
            }

            void set_texture2() {
                set_int("texture2", 2);
            }

            void load_height_0(float height_0) {
                set_float("height_0", height_0);
            }

            void load_height_1(float height_1) {
                set_float("height_1", height_1);
            }

            void load_height_2(float height_2) {
                set_float("height_2", height_2);
            }
    };
}

#endif