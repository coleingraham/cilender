#ifndef MESHDATA_H
#define MESHDATA_H

#include <string>
#include <vector>
#include <map>
#include "cinder/Vector.h"

namespace cilender {

class Cilender;

class MeshData
{
public:
    MeshData();

    std::string name;
    std::vector< ci::Vec3f > verticies;
    std::vector< ci::Vec3f > vertexNormals;
    std::map< std::string, std::vector< ci::Vec3f > > shapekeys;
    std::map< std::string, float > shapekeyValues;
    std::vector< std::vector< int > > faces;
    std::vector< ci::Vec3f > faceNormals;
    std::vector< std::vector< ci::Vec2f > > faceUVs;
    std::vector< std::string > materials;

    static MeshData* loadJSON(std::string fileName);

    void drawMesh(bool useMaterial);
    void drawMesh();

    void setShapeKeyValue(std::string key, float value);
    void updateShapeKeys();
};

}

#endif // MESHDATA_H
