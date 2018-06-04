//
// Created by luiz0tavio on 6/4/18.
//

#ifndef HEDGEHOG_INPUT_HPP
#define HEDGEHOG_INPUT_HPP

#include <SDL2/SDL_events.h>
#include "../renderer/Player.hpp"

namespace Events
{
    class Input
    {
    public:

        static Input& getInstance();

        Input(Input const&) = delete;
        void operator=(Input const&)  = delete;

    private:

        Input() {}

    public:

        bool HandleEvent(Renderer::Player* player) const
        {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {

                auto mouseX = e.motion.x;

                if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)) {
                    return true;
                }

                // Restart if hit 'r'
                if (e.type == SDL_KEYDOWN) {

                    switch (e.key.keysym.sym) {

                        case SDLK_w:
                            player->move(.0f, .01f);
                            break;

                        case SDLK_a:
                            player->move(-.01f, .0f);
                            break;

                        case SDLK_s:
                            player->move(.0f, -.01f);
                            break;

                        case SDLK_d:
                            player->move(.01f, .00f);
                            break;

                        case SDLK_r:

                        default:
                            break;
                    }

                }

                // Restart if hit left mouse button
                if(e.type == SDL_MOUSEBUTTONDOWN) {
                    if (e.button.button == SDL_BUTTON_LEFT) {
                    } else if (e.button.button == SDL_BUTTON_RIGHT) {
                    }
                }
            }
            return false;
        }

    };
}

#endif //HEDGEHOG_INPUT_HPP
