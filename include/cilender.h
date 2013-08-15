#ifndef CILENDER_H
#define CILENDER_H

#include <string>
#include <map>

#include "texturedata.h"
#include "materialdata.h"
#include "meshdata.h"
#include "lampdata.h"
#include "objectdata.h"

namespace cilender {

class Cilender
{
    
public:
    Cilender();

    std::map< std::string, TextureData* > textures;
    std::map< std::string, MaterialData* > materials;
    std::map< std::string, MeshData* > meshes;
    std::map< std::string, LampData* > lamps;
    std::map< std::string, ObjectData* > objects;

    void addJSONTexture(std::string filename);
    void addJSONMaterial(std::string filename);
    void addJSONMesh(std::string filename);
    void addJSONObject(std::string filename);
};

extern Cilender blend;

}

#endif // CILENDER_H
