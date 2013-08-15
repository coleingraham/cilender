#include "include/materialdata.h"
#include "json/json.h"

#include <fstream>

using namespace cilender;

MaterialData::MaterialData()
{
}

MaterialData* MaterialData::loadJSON(std::string fileName)
{
    MaterialData* mat = new MaterialData();

    Json::Value root;
    Json::Reader reader;
    std::ifstream file( fileName.c_str() );
    bool parsingSuccessful = reader.parse( file, root );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse material"
                   << reader.getFormattedErrorMessages();
        return mat;
    }

    std::string name = root.get("name", "").asString();
    ci::ColorA diffuseColor(
                root["diffuseColor"].get("r",0.0).asFloat(),
            root["diffuseColor"].get("g",0.0).asFloat(),
            root["diffuseColor"].get("b",0.0).asFloat(),
            root["diffuseColor"].get("a",0.0).asFloat()
            );
    float diffuseIntensity = root.get("diffuseIntensity",1.0).asFloat();
    ci::ColorA specularColor(
                root["specularColor"].get("r",0.0).asFloat(),
            root["specularColor"].get("g",0.0).asFloat(),
            root["specularColor"].get("b",0.0).asFloat(),
            root["specularColor"].get("a",0.0).asFloat()
            );
    float specularIntensity = root.get("specularIntensity",1.0).asFloat();
    float ambientIntensity = root.get("ambient",1.0).asFloat();
    float emissionIntensity = root.get("emissionIntensity",0.0).asFloat();

    mat->name = name;
    mat->diffuseColor = diffuseColor;
    mat->diffuseIntensity = diffuseIntensity;
    mat->specularColor = specularColor;
    mat->specularIntensity = specularIntensity;
    mat->ambientIntensity = ambientIntensity;
    mat->emissionIntensity = emissionIntensity;

    mat->material = ci::gl::Material(
                ci::ColorA::white() * mat->ambientIntensity,
                mat->diffuseColor * mat->diffuseIntensity,
                mat->specularColor,
                mat->specularIntensity,
                ci::ColorA(
                    mat->diffuseColor.r,
                    mat->diffuseColor.g,
                    mat->diffuseColor.b,
                    mat->emissionIntensity
                    ),
                GL_FRONT
                );

    if(root["textures"].size() > 0)
    {
        std::vector< std::string > textures;
        for(int i=0; i<root["textures"].size(); i++)
        {
            textures.push_back(root["textures"][i].asString());
        }
        mat->textures = textures;
    }

    return mat;
}
