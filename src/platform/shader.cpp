#include "./shader.hpp"

/**
 * @brief Construct a new Shader::Shader object.
 * 
 * @param vert_path vertex shader path
 * @param frag_path fragment shader path
 * @param tessel_control_path tessellation control shader path
 * @param tessel_eval_path tessellation evaluation shader path
 */
Shader::Shader(
    const char* vert_path, 
    const char* frag_path, 
    const char* tessel_control_path, 
    const char* tessel_eval_path
) {
    std::string vert_code = this->read_shader_code(vert_path);
    std::string frag_code = this->read_shader_code(frag_path);

    unsigned int vert = this->create_shader(vert_code.c_str(), "VERTEX");
    unsigned int frag = this->create_shader(frag_code.c_str(), "FRAGMENT");
    std::optional<unsigned int> tessc = std::nullopt;
    std::optional<unsigned int> tesse = std::nullopt;

    try {
        std::string tessel_control_code, tessel_eval_code;

        if (tessel_control_path != nullptr && tessel_eval_path == nullptr) {
            throw "Tessellation Control Shader must be followed by Tessellation Evaluation Shader.";
        } else if (tessel_control_path == nullptr && tessel_eval_path != nullptr) {
            throw "Tessellation Evaluation Shader must be preceded by Tessllation Control Shader.";
        } 
        
        if (tessel_control_path != nullptr && tessel_eval_path != nullptr) {
            tessel_control_code = this->read_shader_code(tessel_control_path);
            tessel_eval_code = this->read_shader_code(tessel_eval_path);

            tessc = this->create_shader(tessel_control_code.c_str(), "TESS CONTROL");
            tesse = this->create_shader(tessel_eval_code.c_str(), "TESS EVALUATION");
        }
    } catch(std::string err) {
        std::cout << "[ERR] " << err << std::endl;
    }

    this->ID = create_shader_program(vert, frag, tessc, tesse);

    glDeleteShader(vert);
    glDeleteShader(frag);
}

/**
 * @brief read shader code from the shader path provided
 * 
 * @param shader_path path to the shader file
 * @return shader code
 */
std::string Shader::read_shader_code(const char* shader_path) {
    std::string shader_code;
    std::ifstream shader_file;

    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        std::stringstream shader_stream;

        shader_file.open(shader_path);
        shader_stream << shader_file.rdbuf();
        shader_file.close();

        shader_code = shader_stream.str();
    } catch (std::ifstream::failure& err) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ::" << err.what() << std::endl;
    }

    return shader_code;
}

/**
 * @brief Create a shader.
 * 
 * @param shader_code the shader code to create the shader.
 * @param shader_type the type of the shader to create.
 * @return a shader of the type specified.
 */
unsigned int Shader::create_shader(const char* shader_code, std::string shader_type) {
    int type;

    if (shader_type == "VERTEX") {
        type = GL_VERTEX_SHADER;
    } else if (shader_type == "FRAGMENT") {
        type = GL_FRAGMENT_SHADER;
    } else if (shader_type == "TESS CONTROL") {
        type = GL_TESS_CONTROL_SHADER;
    } else if (shader_type == "TESS EVALUATION") {
        type = GL_TESS_EVALUATION_SHADER;
    } else {
        type = 0;
        std::cout << "[ERR] Shader type " << shader_type << " not found. Available types are: VERTEX, FRAGMENT, TESS CONTROL, TESS EVALUATION.";
    }

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);

    check_compile_errors(shader, shader_type);

    return shader;
}

/**
 * @brief Creates a shader program.
 * 
 * @param vert vertex shader ID
 * @param frag fragment shader ID
 * @param tcs tesselation control shader ID. Defaults to `std::nullopt`
 * @param tes tessellation evaluation shader ID. Defaults to `std::nullopt`
 * @return shader program ID
 */
unsigned int Shader::create_shader_program(
    unsigned int vert, 
    unsigned int frag,
    std::optional<unsigned int> tessc,
    std::optional<unsigned int> tesse
) {
    unsigned int ID = glCreateProgram();    // the program ID

    glAttachShader(ID, vert);
    glAttachShader(ID, frag);

    if (tessc.has_value()) {
        glAttachShader(ID, tessc.value());
    }

    if (tesse.has_value()) {
        glAttachShader(ID, tesse.value());
    }

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

void Shader::set_vec3(const std::string &name, glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, &value[0]);
}

void Shader::set_vec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
}

void Shader::set_mat4(const std::string &name, glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}