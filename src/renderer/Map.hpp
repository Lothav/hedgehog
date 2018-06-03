//
// Created by luiz0tavio on 6/3/18.
//

#ifndef HEDGEHOG_MAP_HPP
#define HEDGEHOG_MAP_HPP

#include <vector>
#include <Tmx.h>
#include "Object2D.hpp"

namespace Renderer
{

    struct Layer {

        std::vector<Object2D *> data;
    };

    class Map
    {

    private:

        std::vector<Layer *> layers_;

    public:

        Map() {}

        std::vector<Layer *> getLayers() const;

        void loadLayersFromTmxFile(const std::string& path, const GLfloat scale);

    };
}


#endif //HEDGEHOG_MAP_HPP
