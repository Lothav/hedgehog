#include <functional>
#include <memory>
#include <SDL2/SDL_image.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "renderer/Window.hpp"
#include "renderer/BulkText.hpp"

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

        auto *SDL_window = window->getWindow();

        GLfloat white_color[4] {1.f, 1.f, 1.f, 1.f};

        auto text_velocity = std::make_shared<Renderer::Text>(-1.f, -1.f, 48, white_color);
        text_velocity->setText("Test");
        Renderer::BulkText::getInstance().push_back(text_velocity);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        auto loop = [&]() -> bool {

            auto start = SDL_GetTicks();

            // Set screen to black
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            Renderer::BulkText::getInstance().draw(window->getSize());

            // Swap Window
            SDL_GL_SwapWindow(SDL_window);

            // Adjust FPS
            if (1000/60 > (SDL_GetTicks() - start)) {
                SDL_Delay(1000/60 - (SDL_GetTicks() - start));
            }

#ifdef DEBUG
            return false;
#else
            return true;
#endif
        };

        while(loop());

        SDL_GL_DeleteContext(mainContext);
    }

    Memory::Provider::destroyPools();
    SDL_Quit();
    glEnd();
    return EXIT_SUCCESS;
}