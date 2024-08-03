#include "texture_generator.hpp"

TexturePack::TexturePack(std::vector<const char*> paths) {
    for (const char* path: paths) {
        textures.push_back(Texture(path));
    }
}

void TexturePack::bind() {
    int texture_iterator = GL_TEXTURE0;

    for (Texture texture: textures) {
        glActiveTexture(texture_iterator);
        texture.bind();
        texture_iterator += 1;
    }
}