//
// Created by luiz0tavio on 6/4/18.
//

#ifndef HEDGEHOG_PLAYER_HPP
#define HEDGEHOG_PLAYER_HPP


#include "Object2D.hpp"

#include <vector>

namespace Renderer
{
    struct Texture {
        std::string path;
        GLuint id;
    };

    enum Orientation {
        DOWN,
        LEFT,
        LEFT_DOWN,
        LEFT_UP,
        RIGHT,
        RIGHT_DOWN,
        RIGHT_UP,
        UP
    };

    struct Animation {
        std::string state;
        std::string base_path;
        int size;
        Orientation orientation;
    };


    class Player : public Object2D
    {

    private:

        std::map<std::string, std::map<Orientation, std::vector<Texture>>> animations_;
        int animation_frame_;
        std::string animation_state_;
        Orientation orientation_;

    public:

        Player(const std::vector<Animation>& animations) : Object2D(Position{.x = .0f, .y = .0f}, Size{.height = .16f, .width = .16f}, true)
        {
            this->orientation_ = animations[0].orientation;
            this->animation_state_ = animations[0].state;

            for (auto& animation: animations) {
                for (int i = 0; i < animation.size; i++) {
                    std::string path = animation.base_path;
                    path += (i >= 10 ? "" : "0");
                    path += std::to_string(i) + ".png";

                    this->setTexture(path, GL_RGBA);

                    Texture text;
                    text.path = path;
                    text.id = this->getTextureId();

                    this->animations_[animation.state][animation.orientation].push_back(text);
                }
            }
        }

        void updateAnimationFrame()
        {
            auto animations_vec = this->animations_[this->animation_state_][this->orientation_];
            this->animation_frame_ ++;
            if (this->animation_frame_ >= animations_vec.size()) this->animation_frame_ = 0;
            this->texture_id_ = animations_vec[this->animation_frame_].id;
        }

        void move(GLfloat x, GLfloat y)
        {
            for (int i = 0; i < SIZE_VERTICES; i += COORDINATES_BY_VERTEX) {
                this->vertices_[i] += x;
            }

            for (int i = 1; i < SIZE_VERTICES; i += COORDINATES_BY_VERTEX) {
                this->vertices_[i] += y;
            }
        }

    };
}



#endif //HEDGEHOG_PLAYER_HPP
