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

    const Json::Value skey = root["shapekeys"];
    if(skey.size() > 0)
    {
        std::map< std::string, std::vector< ci::Vec3f > > shapekeys;
        for(int i=0; i<skey.size(); i++)
        {
            std::string key = skey[i].get("name","").asString();
            std::vector< ci::Vec3f > value;

            for(int j=0; j<skey[i]["verts"].size(); j++)
            {
                value.push_back(
                            ci::Vec3f(
                                skey[i]["verts"][j].get("x",0.0).asFloat(),
                            skey[i]["verts"][j].get("y",0.0).asFloat(),
                        skey[i]["verts"][j].get("z",0.0).asFloat()
                        )
                        );
            }
            shapekeys[key] = value;
        }

        mesh->shapekeys = shapekeys;

        const Json::Value skeyVal = root["shapekeyValues"];
        std::map< std::string, float > shapekeyValues;
        for(int i=0; i<skeyVal.size(); i++)
        {
            shapekeyValues[skeyVal[i].get("name","").asString()] = skeyVal[i].get("value",0.0).asFloat();
        }

        mesh->shapekeyValues = shapekeyValues;
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

    const Json::Value uv = root["faceUVs"];
    if(uv.size() > 0)
    {
        std::vector< std::vector< ci::Vec2f > > faceUVs;
        for(int i=0; i<uv.size(); i++)
        {
            std::vector< ci::Vec2f > uvs;
            for(int j=0; j<uv[i].size(); j++)
            {
                uvs.push_back(
                            ci::Vec2f(
                                uv[i][j].get("x",0.0).asFloat(),
                                uv[i][j].get("y",0.0).asFloat()
                                )
                            );
            }
            faceUVs.push_back(uvs);
        }
        mesh->faceUVs = faceUVs;
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

    return mesh;
}

void MeshData::drawMesh()
{
    drawMesh(true);
}

void MeshData::drawMesh(bool useMaterial)
{
    if(useMaterial)
    {
        cilender::data.materials[ materials[0] ]->material.apply();
        cilender::data.textures[ cilender::data.materials[ materials[0] ]->textures[0] ]->texture.bind(0);
    }

    for(int i=0; i<faces.size(); i++)
    {
        ci::gl::begin(GL_POLYGON);
        for(int j=0; j<faces[i].size(); j++)
        {
            if(faceUVs.size() > 0)
            {
                glTexCoord2f( faceUVs[i][j].x, faceUVs[i][j].y );
            }
            ci::gl::vertex(verticies[ faces[i][j] ] );
        }

        ci::gl::end();
    }

    if(useMaterial)
    {
        cilender::data.textures[ cilender::data.materials[ materials[0] ]->textures[0] ]->texture.unbind(0);
    }
}

void MeshData::setShapeKeyValue(std::string key, float value)
{
    shapekeyValues[key] = value;
}

void MeshData::updateShapeKeys()
{
    // reset our verticies to Basis first
    for(int i=0; i<verticies.size(); i++)
    {
        verticies[i].set(shapekeys["Basis"][i]);
    }

    float weightScale = 0.0;

    for(std::map< std::string, float >::iterator it = shapekeyValues.begin(); it != shapekeyValues.end(); ++it)
    {
        if(it->first == "Basis") { continue; }

        weightScale += it->second;
    }

    weightScale = 1/weightScale;

    for(std::map< std::string, std::vector< ci::Vec3f > >::iterator it = shapekeys.begin(); it != shapekeys.end(); ++it)
    {
        if(it->first == "Basis") { continue; }

        for(int i=0; i<shapekeys[it->first].size(); i++)
        {
            if(shapekeyValues[it->first] > 0.0)
            {
                if(shapekeys[it->first][i] != shapekeys["Basis"][i])
                {
                    verticies[i].lerpEq(shapekeyValues[it->first] * weightScale, shapekeys[it->first][i] );
                }
            }
        }
    }
}
