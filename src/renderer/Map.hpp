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

        std::vector<Layer *> getLayers() const
        {
            return this->layers_;
        }

        void loadLayersFromTmxFile(const std::string& path, const GLfloat scale)
        {
            auto map_instance = new Tmx::Map();
            map_instance->ParseFile(path);

            if (map_instance->HasError()) {
                std::cout << map_instance->GetErrorCode() << std::endl;
            }

            for (int i = 0; i < map_instance->GetNumTileLayers(); i++) {

                auto layer = new Layer;

                auto tile_layer = map_instance->GetTileLayer(i);
                for (int y = 0; y < tile_layer->GetHeight(); y++) {
                    for (int x = 0; x < tile_layer->GetWidth(); x++) {

                        if (tile_layer->GetTileTilesetIndex(x, y) == -1) {
                            continue;
                        }

                        auto tile = tile_layer->GetTile(x, y);
                        if (tile.tilesetId == -1) {
                            continue;
                        }

                        auto img = map_instance->GetTileset(tile.tilesetId)->GetTile(tile.id)->GetImage();

                        auto w = static_cast<GLfloat>(img->GetWidth())  * scale;
                        auto h = static_cast<GLfloat>(img->GetHeight()) * scale;

                        auto offset_w = static_cast<GLfloat>(img->GetWidth()) / static_cast<GLfloat>(map_instance->GetTileWidth());
                        auto offset_h = static_cast<GLfloat>(img->GetHeight()) / static_cast<GLfloat>(map_instance->GetTileHeight());

                        auto tile_obj2d = new Renderer::Object2D(
                            Position {
                                .x =  ((x - y) * (w / (2.f*offset_w))),
                                .y = -((x + y) * (h / (2.f*offset_h))),
                                .z = 0.f
                            },
                            Size {
                                .height = h,
                                .width  = w,
                            }
                        );

                        tile_obj2d->setTexture("./data/maps/" + img->GetSource(), GL_RGBA);

                        layer->data.push_back(tile_obj2d);
                    }
                }

                this->layers_.push_back(layer);
            }
        }

    };
}


#endif //HEDGEHOG_MAP_HPP
