#ifndef MATERIALDATA_H
#define MATERIALDATA_H

#include <string>
#include <vector>
#include "cinder/Color.h"
#include "cinder/gl/Material.h"

namespace cilender {

class MaterialData
{
public:
    MaterialData();

    std::string name;
    ci::ColorA diffuseColor;
    float diffuseIntensity;
    ci::ColorA specularColor;
    float specularIntensity;
    float ambientIntensity;
    float emissionIntensity;
    std::vector< std::string > textures;

    ci::gl::Material material;

    static MaterialData *loadJSON(std::string fileName);
};

}

#endif // MATERIALDATA_H
