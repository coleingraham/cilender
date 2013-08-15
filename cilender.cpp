#include "include/cilender.h"

using namespace cilender;

Cilender::Cilender()
{
}

void Cilender::addJSONTexture(std::string filename)
{
    cilender::TextureData* tex = cilender::TextureData::loadJSON(filename);
    textures[tex->name] = tex;
}

void Cilender::addJSONMaterial(std::string filename)
{
    cilender::MaterialData* mat = cilender::MaterialData::loadJSON(filename);
    materials[mat->name] = mat;
}

void Cilender::addJSONMesh(std::string filename)
{
    cilender::MeshData* m = cilender::MeshData::loadJSON(filename);
    meshes[m->name] = m;
}

void Cilender::addJSONObject(std::string filename)
{
//    cilender::ObjectData* o = cilender::ObjectData::loadJSON(filename);
//    objects[o->name] = o;
}
