//
// Created by luiz0tavio on 6/2/18.
//

#ifndef BREAKOUT_OBJECT2D_HPP
#define BREAKOUT_OBJECT2D_HPP

#include <GL/glew.h>
#include <array>

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

    public:

        Object2D(Position position, Size size) : pos_(position), size_(size)
        {

            auto x = position.x;
            auto y = position.y;

            auto width = size.width;
            auto height = size.height;

            this->vertices_ = {
                // Triangles                                            c ___
                x + (width/2), y + (height/2), 0.0f, 1.0f, 0.0f, // a    |  /a
                x - (width/2), y - (height/2), 0.0f, 0.0f, 1.0f, // b    | /
                x - (width/2), y + (height/2), 0.0f, 0.0f, 0.0f, // c   b|/

                x + (width/2), y + (height/2), 0.0f, 1.0f, 0.0f, // d       /|d
                x - (width/2), y - (height/2), 0.0f, 0.0f, 1.0f, // e      / |
                x + (width/2), y - (height/2), 0.0f, 1.0f, 1.0f, // f    e/__|f
            };
        }

    };
}


#endif //BREAKOUT_OBJECT2D_HPP
