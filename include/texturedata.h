#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include <string>
#include "cinder/gl/Texture.h"

namespace cilender {

class TextureData
{
public:
    TextureData();

    std::string name;
    ci::gl::Texture texture;

    static TextureData* loadJSON(std::string fileName);
};

}

#endif // TEXTUREDATA_H
