#include "include/meshdata.h"
#include "include/cilender.h"
#include "json/json.h"
#include "cinder/gl/gl.h"

#include <fstream>

using namespace cilender;

MeshData::MeshData()
{
}

MeshData *MeshData::loadJSON(std::string fileName)
{
    MeshData* mesh = new MeshData();

    Json::Value root;
    Json::Reader reader;
    std::ifstream file( fileName.c_str() );
    bool parsingSuccessful = reader.parse( file, root );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse mesh"
                   << reader.getFormattedErrorMessages();

        return mesh;
    }

    std::string name = root.get("name", "").asString();

    std::vector< ci::Vec3f > verticies;
    const Json::Value verts = root["verts"];
    for(int i=0; i<verts.size(); i++)
    {
        verticies.push_back(
                    ci::Vec3f(
                        verts[i].get("x",0.0).asFloat(),
                        verts[i].get("y",0.0).asFloat(),
                        verts[i].get("z",0.0).asFloat()
                        )
                    );
    }

    std::vector< ci::Vec3f > vertexNormals;
    const Json::Value vertNormals = root["vertNormals"];
    for(int i=0; i<vertNormals.size(); i++)
    {
        vertexNormals.push_back(
                    ci::Vec3f(
                        vertNormals[i].get("x",0.0).asFloat(),
                        vertNormals[i].get("y",0.0).asFloat(),
                        vertNormals[i].get("z",0.0).asFloat()
                        )
                    );
    }

    std::vector< std::vector< int > > faces;
    const Json::Value face = root["faces"];
    for(int i=0; i<face.size(); i++)
    {
        std::vector< int > list;
        for(int j=0; j<face[i].size(); j++)
        {
            list.push_back( face[i][j].asInt() );
        }
        faces.push_back( list );
    }

    std::vector< ci::Vec3f > faceNormals;
    const Json::Value faceNor = root["faceNormals"];
    for(int i=0; i<vertNormals.size(); i++)
    {
        faceNormals.push_back(
                    ci::Vec3f(
                        faceNor[i].get("x",0.0).asFloat(),
                        faceNor[i].get("y",0.0).asFloat(),
                        faceNor[i].get("z",0.0).asFloat()
                        )
                    );
    }

    std::vector< std::string > mat;
    const Json::Value matName = root["materials"];
    for(int i=0; i<matName.size(); i++)
    {
        mat.push_back(matName[i].asString());
    }

    mesh->name = name;
    mesh->verticies = verticies;
    mesh->vertexNormals = vertexNormals;
    mesh->faces = faces;
    mesh->faceNormals = faceNormals;
    mesh->materials = mat;

    // add faceUVs, shapekeys, later

    return mesh;
}

void MeshData::drawMesh()
{
    cilender::data.materials[ materials[0] ]->material.apply();

    for(int i=0; i<faces.size(); i++)
    {
        ci::gl::begin(GL_POLYGON);
        for(int j=0; j<faces[i].size(); j++)
        {
            ci::gl::vertex(verticies[ faces[i][j] ] );
        }

        ci::gl::end();
    }
}
