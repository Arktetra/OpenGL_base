#ifndef TEXTURE_GENERATOR_HPP
#define TEXTURE_GENERATOR_HPP

#include <vector>

#include "platform/texture.hpp"

class TexturePack {
    std::vector<Texture> textures;

    public:
        TexturePack(std::vector<const char*> paths);
        void bind();
};

#endif