#include "./utils.hpp"

void Debug::init() {
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(Debug::output, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
}

void Debug::output(
    GLenum source,
    GLenum type,
    unsigned int id,
    GLenum severity,
    GLsizei length,
    const char *message,
    const void *user_param
) {
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;
    
    std::cout << "-------------------------------------------------------------" << std::endl;
    std::cout << "Debug Message (" << id << ") " << message << std::endl;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            std::cout << "Source: API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            std::cout << "Source: Window System";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            std::cout << "Source: Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            std::cout << "Source: Third Party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            std::cout << "Source: Application";
            break;
        case GL_DEBUG_SOURCE_OTHER: 
            std::cout << "Source: Other";
            break;
    } std::cout << std::endl;

    switch (type) {
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "Type: Deprecated Behavior";
            break;
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "Type: Error";
            break;
        case GL_DEBUG_TYPE_MARKER:
            std::cout << "Type: Marker";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "Type: Other";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "Type: Performance";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            std::cout << "Type: Pop Group";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "Type: Undefined Behavior";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            std::cout << "Type: Push Group";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "Type: Portability";
            break;
    } std::cout << std::endl;

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "Severity: High";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "Severity: Medium";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "Severity: Low";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "Severity: Notification";
            break;
    } std::cout << std::endl;

    std::cout << "Length: " << length << std::endl;
    std::cout << "User parameters: " << user_param << std::endl;

    std::cout << std::endl;
} 

/**
 * @brief configure the vertex attribute.
 * 
 * @param attrib_pointer the location of the vertex attribute.
 * @param size size of the vertex attribute. If the vertex attribute is a `vec3`, it is equal to 3.
 * @param stride distance between two consecutive vertex attributes.
 * @param offset position where the data begins in the buffer
 * 
 * @overload
 */
void ProcGen::config_vertex_attribute(
    int attrib_pointer,
    int size,
    int stride,
    void* offset
) {
    glVertexAttribPointer(attrib_pointer, size, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(attrib_pointer);
}

/**
 * @brief configure vertex attribute for position, color and texture.
 * 
 * @param pos_attrib_pointer the location of the position vertex attribute.
 * @param col_attrib_pointer the location of the color vertex attribute.
 * @param tex_attrib_pointer the location of the texture vertex attribute.
 * @param pos_size size of the position vertex attribute: x, y and z.
 * @param col_size size o the color vertex attribute: R, G, B and A.
 * @param tex_size size of the texture vertex attribute: s, t and r.
 * @param stride 
 * @param pos_offset 
 * @param col_offset 
 * @param tex_offset 
 */
void ProcGen::config_vertex_attribute(
    int pos_attrib_pointer,
    int col_attrib_pointer,
    int tex_attrib_pointer,
    int pos_size,
    int col_size,
    int tex_size,
    int stride,
    void* pos_offset,
    void* col_offset,
    void* tex_offset
) {
    ProcGen::config_vertex_attribute(pos_attrib_pointer, pos_size, stride, pos_offset);
    ProcGen::config_vertex_attribute(col_attrib_pointer, col_size, stride, col_offset);
    ProcGen::config_vertex_attribute(tex_attrib_pointer, tex_size, stride, tex_offset);
}