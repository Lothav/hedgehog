#include <functional>
#include <memory>
#include <SDL2/SDL_image.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "renderer/Window.hpp"
#include "renderer/BulkText.hpp"
#include "renderer/Object2D.hpp"
#include "renderer/BulkObject2D.hpp"

#include "Tmx.h"

void update()
{

}

int main(int argc, char* argv[])
{
    Memory::Provider::initPools();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Could not initialize sdl2: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == 0) {
        std::cerr << "Could not initialize IMG's flags" << std::endl;
        return EXIT_FAILURE;
    }

    {
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        std::array<int, 2> window_default_size = {DM.w, DM.h};

        auto window = std::make_unique<Renderer::Window>(window_default_size);

        auto mainContext = SDL_GL_CreateContext(window->getWindow());

        GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cerr << "Glew is not ok =(" << std::endl;
            return EXIT_FAILURE;
        }

        if (!GLEW_VERSION_2_0) {
            std::cerr << "Error: your graphic card does not support OpenGL 2.0" << std::endl;
            return EXIT_FAILURE;
        }

        auto map_instance = new Tmx::Map();
        map_instance->ParseFile("data/maps/0002.tmx");

        if (map_instance->HasError()) {
            std::cout << map_instance->GetErrorCode() << std::endl;
        }

        for (int i = 0; i < map_instance->GetNumTileLayers(); i++) {

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

                    std::cout << tile.gid << " ";

                    auto tile_obj = map_instance->GetTileset(tile.tilesetId)->GetTile(tile.id);

                    auto img = tile_obj->GetImage();

                    auto w = static_cast<GLfloat>(img->GetWidth())  / 2000.f;
                    auto h = static_cast<GLfloat>(img->GetHeight()) / 2000.f;

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
                    Renderer::BulkObject2D::getInstance().push_back(tile_obj2d);
                }
                std::cout << std::endl;
            }
        }

        GLfloat white_color[4] {1.f, 1.f, 1.f, 1.f};
        auto text_velocity = std::make_shared<Renderer::Text>(-1.f, -1.f, 48, white_color);
        text_velocity->setText("Test");
        Renderer::BulkText::getInstance().push_back(text_velocity);

        auto player = std::make_shared<Renderer::Object2D> (
            Position{.x = 0, .y = 0, .z = 0},
            Size{.height = 0.06f, .width = 0.24f}
        );

        player->setTexture("./data/breakout-blocks-texture.jpg", GL_RGB);
        Renderer::BulkObject2D::getInstance().push_back(player.get());

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        auto loop = [&]() -> bool {

            auto start = SDL_GetTicks();

            // Set screen to black
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            Renderer::BulkObject2D::getInstance().draw();
            Renderer::BulkText::getInstance().draw(window->getSize());

            update();

            // Swap Window
            SDL_GL_SwapWindow(window->getWindow());

            // Adjust FPS
            if (1000/60 > (SDL_GetTicks() - start)) {
                SDL_Delay(1000/60 - (SDL_GetTicks() - start));
            }

            return true;
        };

        while(loop());

        SDL_GL_DeleteContext(mainContext);
    }

    Memory::Provider::destroyPools();
    SDL_Quit();
    glEnd();

    return EXIT_SUCCESS;
}