#include "include/cilender.h"

namespace cilender
{
/**
 * @brief data
 * global access to storage for all blender data we have loaded
 */
Cilender data;
}

using namespace cilender;

Cilender::Cilender()
{
}

/**
 * @brief Cilender::addJSONTexture
 * @param filename
 * create a new TextureData object from a JSON file and add it to our global map
 */
void Cilender::addJSONTexture(std::string filename)
{
    TextureData* tex = TextureData::loadJSON(filename);
    textures[tex->name] = tex;
}

/**
 * @brief Cilender::addJSONMaterial
 * @param filename
 * create a new MaterialData object from a JSON file and add it to our global map
 */
void Cilender::addJSONMaterial(std::string filename)
{
    MaterialData* mat = MaterialData::loadJSON(filename);
    materials[mat->name] = mat;
}

/**
 * @brief Cilender::addJSONMesh
 * @param filename
 * create a new MeshData object from a JSON file and add it to our global map
 */
void Cilender::addJSONMesh(std::string filename)
{
    MeshData* m = MeshData::loadJSON(filename);
    meshes[m->name] = m;
}

/**
 * @brief Cilender::addJSONObject
 * @param filename
 * create a new ObjectData object from a JSON file and add it to our global map
 */
void Cilender::addJSONObject(std::string filename)
{
    //    ObjectData* o = ObjectData::loadJSON(filename);
    //    objects[o->name] = o;
}

/**
 * @brief Cilender::cleanup
 * delete all the data we have been storing
 */
void Cilender::cleanup()
{
    for(std::map< std::string, TextureData* >::iterator iter = textures.begin(); iter != textures.end(); ++iter)
    {
        delete iter->second;
    }

    for(std::map< std::string, MaterialData* >::iterator iter = materials.begin(); iter != materials.end(); ++iter)
    {
        delete iter->second;
    }

    for(std::map< std::string, MeshData* >::iterator iter = meshes.begin(); iter != meshes.end(); ++iter)
    {
        delete iter->second;
    }

    for(std::map< std::string, LampData* >::iterator iter = lamps.begin(); iter != lamps.end(); ++iter)
    {
        delete iter->second;
    }

    for(std::map< std::string, ObjectData* >::iterator iter = objects.begin(); iter != objects.end(); ++iter)
    {
        delete iter->second;
    }
}
