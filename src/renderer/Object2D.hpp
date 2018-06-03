//
// Created by luiz0tavio on 6/2/18.
//

#ifndef BREAKOUT_OBJECT2D_HPP
#define BREAKOUT_OBJECT2D_HPP

#include <GL/glew.h>
#include <array>
#include <SDL2/SDL_image.h>
#include "../memory/Pool.hpp"
#include "../memory/Provider.hpp"

#define COORDINATES_BY_VERTEX 5   // 5 coords each (x, y, z, u, v)
#define TOTAL_VERTICES 6          // 6 points (two triangles

#define SIZE_VERTICES TOTAL_VERTICES*COORDINATES_BY_VERTEX


struct Position {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct Size {
    GLfloat height;
    GLfloat width;
};

namespace Renderer
{
    class Object2D
    {

    private:

        Position pos_;
        Size size_;

        // Six vetices = 2 triangles.
        std::array<GLfloat, SIZE_VERTICES> vertices_;

        GLuint texture_id_;
        GLuint vbo_;

    public:

        Object2D(Position position, Size size) : pos_(position), size_(size)
        {
            auto x = position.x;
            auto y = position.y;

            auto width = size.width;
            auto height = size.height;

            this->vertices_ = {
                // Triangles                                                c ___
                x + (width/2.f), y + (height/2.f), 0.0f, 1.0f, 0.0f, // a    |  /a
                x - (width/2.f), y - (height/2.f), 0.0f, 0.0f, 1.0f, // b    | /
                x - (width/2.f), y + (height/2.f), 0.0f, 0.0f, 0.0f, // c   b|/

                x + (width/2.f), y + (height/2.f), 0.0f, 1.0f, 0.0f, // d       /|d
                x - (width/2.f), y - (height/2.f), 0.0f, 0.0f, 1.0f, // e      / |
                x + (width/2.f), y - (height/2.f), 0.0f, 1.0f, 1.0f, // f    e/__|f
            };

            glGenBuffers(1, &this->vbo_);
        }

        void setTexture(const std::string& path, const GLenum format)
        {
            SDL_Surface* surf = IMG_Load(path.c_str());

            glGenTextures(1, &this->texture_id_);
            glBindTexture(GL_TEXTURE_2D, this->texture_id_);
            glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, surf->w, surf->h);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0 ,0, surf->w, surf->h, format, GL_UNSIGNED_BYTE, surf->pixels);

            free(surf);

            unsigned int error_code = glGetError();
            if (error_code != GL_NO_ERROR) {
                std::cerr << "OpenGL error glTexImage2D. Error code: " << std::to_string(error_code) << std::endl;
            }

            glGenerateMipmap(GL_TEXTURE_2D);
        }

        GLuint getTextureId()
        {
            return this->texture_id_;
        }

        GLuint getVBO()
        {
            return this->vbo_;
        }

        std::array<GLfloat, SIZE_VERTICES> getVertices()
        {
            return this->vertices_;
        };

        void * operator new (std::size_t size)
        {
            return Memory::Provider::getMemory(Memory::PoolType::POOL_TYPE_GENERIC, size);
        }

        void  operator delete (void* ptr, std::size_t) {}

    };
}


#endif //BREAKOUT_OBJECT2D_HPP
