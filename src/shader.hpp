#ifndef SHADER_H
#define SHADER_H

#include "./includes/GLAD/glad.h"


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    unsigned int ID;
    unsigned int create_vert_shader(const char* vert_shader_code);
    unsigned int create_frag_shader(const char* frag_shader_code);
    unsigned int create_shader_program(unsigned int vert, unsigned int frag);
    void check_compile_errors(unsigned int shader, std::string type);

    public:
        Shader(const char* vert_path, const char* frag_path);
        void use();
        unsigned int get_id();
        void remove();
        void set_bool(const std::string &name, bool value) const;
        void set_int(const std::string &name, int value) const;
        void set_uint(const std::string &name, int value) const;
        void set_float(const std::string &name, float value) const;
};

#endif