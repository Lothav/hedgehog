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

        GLuint vbo_;

        bool fixed_;

        bool has_depth_;

    protected:

        // Current texture id
        GLuint texture_id_;

        // Six vetices = 2 triangles.
        std::array<GLfloat, SIZE_VERTICES> vertices_;

    public:

        Object2D(Position position, Size size, bool fixed, bool has_depth);

        void setTexture(const std::string& path, const GLenum format);

        GLuint getTextureId();

        GLuint getVBO();

        std::array<GLfloat, SIZE_VERTICES> getVertices();

        bool getFixed() const
        {
            return this->fixed_;
        }

        bool hasDepth() const
        {
            return this->has_depth_;
        }

        void * operator new (std::size_t size);

        void  operator delete (void* ptr, std::size_t) {}

    };
}


#endif //BREAKOUT_OBJECT2D_HPP
