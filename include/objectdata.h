#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include <string>
#include <vector>
#include <map>
#include "cinder/Vector.h"

namespace cilender {

class ObjectData
{
public:
    ObjectData();

    std::string name;
    std::string data;
    ci::Vec3f location;
    ci::Vec3f rotation;
    ci::Vec3f scale;
    std::vector< bool > layers;
};

}

#endif // OBJECTDATA_H
