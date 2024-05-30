#include "./shader.hpp"

/// @brief Create a shader program.
/// @param vert_path path to the vertex shader.
/// @param frag_path path to the fragment shader.

/**
 * Create a shader program.
 * 
 * # Parameters
 * `vert_path` -  path to the vertex shader.
 * `frag_path` -  path to the fragment shader.
 */
Shader::Shader(const char* vert_path, const char* frag_path) {
    std::string vert_code;
    std::string frag_code;
    std::ifstream vert_shader_file;
    std::ifstream frag_shader_file;

    vert_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    frag_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        std::stringstream vert_shader_stream;

        vert_shader_file.open(vert_path);
        vert_shader_stream << vert_shader_file.rdbuf();
        vert_shader_file.close();

        vert_code = vert_shader_stream.str();
    } catch (std::ifstream::failure& err) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ::" << err.what() << std::endl;
    }

    try {
        std::stringstream frag_shader_stream;

        frag_shader_file.open(frag_path);
        frag_shader_stream << frag_shader_file.rdbuf();
        frag_shader_file.close();

        frag_code = frag_shader_stream.str();
    } catch (std::ifstream::failure& err) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ::" << err.what() << std::endl;
    }  

    unsigned int vert = this->create_vert_shader(vert_code.c_str());
    unsigned int frag = this->create_frag_shader(frag_code.c_str());

    this->ID = create_shader_program(vert, frag);

    glDeleteShader(vert);
    glDeleteShader(frag);
}

/**
 * create a vertex shader
 * 
 * # Parameters
 * vert_shader_code vertex shader code
 * 
 * # Returns
 * vertex shader ID
 */
unsigned int Shader::create_vert_shader(const char* vert_shader_code) {
    // std::cout << vert_shader_code << std::endl;

    unsigned int vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vert_shader_code, NULL);
    glCompileShader(vert);

    check_compile_errors(vert, "VERTEX");

    return vert;
}

/**
* create a fragment shader
* 
* # Parameters
* `frag_shader_code` -  fragment shader code
* `fragment shader` - ID
*/
unsigned int Shader::create_frag_shader(const char* frag_shader_code) {
    unsigned int frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &frag_shader_code, NULL);
    glCompileShader(frag);

    check_compile_errors(frag, "FRAGMENT");

    return frag;
}

/**
 * create a shader program
 * 
 * # Parameters
 * `vert` - vertex shader ID
 * `frag` - fragment shader ID
 * 
 * # Returns
 * shader program ID
 */
unsigned int Shader::create_shader_program(unsigned int vert, unsigned int frag) {
    unsigned int ID = glCreateProgram();
    glAttachShader(ID, vert);
    glAttachShader(ID, frag);
    glLinkProgram(ID);

    check_compile_errors(ID, "PROGRAM");

    return ID;
}

/**
 * check for compilation or linking errors of the shaders
 * 
 * # Parameters
 * `shader (unsigned int)`: the shader program
 * `type (std::string)`: should be "`"PROGRAM"`, `"VERTEX"` or `"FRAGMENT"`
 */
void Shader::check_compile_errors(unsigned int shader, std::string type) {
    
    int success;
    char info_log[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, info_log);
            std::cout << "ERROR::SHADER::COMPILATION::ERROR::" << type << "\n" << info_log << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, info_log);
            std::cout << "ERROR::PROGRAM::LINKING::ERROR::" << type << "\n" << info_log << std::endl;
        }
    }
}

void Shader::use() {
    glUseProgram(this->ID);
}

unsigned int Shader::get_id() {
    return this->ID;
}

void Shader::remove() {
    glDeleteProgram(this->ID);
}

void Shader::set_bool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::set_int(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::set_uint(const std::string &name, int value) const {
    glUniform1ui(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::set_float(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::set_mat4(const std::string &name, glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}