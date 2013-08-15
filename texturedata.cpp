#include "include/texturedata.h"
#include "cinder/Cinder.h"
#include "cinder/ImageIo.h"
#include "cinder/CinderResources.h"
#include "json/json.h"

#include <fstream>

using namespace cilender;

TextureData::TextureData()
{
}

TextureData *TextureData::loadJSON(std::string fileName)
{
    TextureData* tex = new TextureData();

    Json::Value root;
    Json::Reader reader;
    std::ifstream file( fileName.c_str() );
    bool parsingSuccessful = reader.parse( file, root );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << "Failed to parse texture\n"
                   << reader.getFormattedErrorMessages();
        return tex;
    }

    std::string name = root.get("name", "").asString();
    std::string textureFileName = root.get("image", "").asString();

    tex->name = name;
    tex->texture = ci::gl::Texture( ci::loadImage(textureFileName) );

    return tex;
}
