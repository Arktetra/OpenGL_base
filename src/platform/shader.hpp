#ifndef SHADER_H
#define SHADER_H

#include "../includes/GLAD/glad.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <optional>

namespace OpenGLBase {
    class Shader {
        unsigned int ID;    // shader program ID
        unsigned int create_shader(const char* shader_code, std::string shader_type);

        unsigned int create_shader_program(
            unsigned int vert,  // vertex shader ID
            unsigned int frag,  // fragment shader ID
            std::optional<unsigned int> tessc = std::nullopt,   // tessellation control shader ID
            std::optional<unsigned int> tesse = std::nullopt    // tessellation evaluation shader ID
        );

        void check_compile_errors(unsigned int shader, std::string type);
        std::string read_shader_code(const char* shader_path);

        public:
            Shader() {}
            // Shader(const char* vert_path, const char* frag_path);
            Shader(
                const char* vert_path, 
                const char* frag_path, 
                const char* tessel_control_path = nullptr, 
                const char* tessel_eval_path = nullptr
            );

            void use();
            unsigned int get_id();
            void remove();

            void set_bool(const std::string &name, bool value) const;
            void set_int(const std::string &name, int value) const;
            void set_uint(const std::string &name, int value) const;
            void set_float(const std::string &name, float value) const;
            void set_vec3(const std::string &name, glm::vec3 &vec) const;
            void set_vec3(const std::string &name, float x, float y, float z) const;
            void set_vec4(const std::string &name, glm::vec4 &vec) const;
            void set_mat4(const std::string &name, glm::mat4 &mat) const;
    };
}

#endif