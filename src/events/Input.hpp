//
// Created by luiz0tavio on 6/4/18.
//

#ifndef HEDGEHOG_INPUT_HPP
#define HEDGEHOG_INPUT_HPP

#include <SDL2/SDL_events.h>

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

        bool HandleEvent() const
        {
            SDL_Event e;
            while (SDL_PollEvent(&e)) {

                auto mouseX = e.motion.x;

                if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)) {
                    return true;
                }

                // Restart if hit 'r'
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_r) {

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
