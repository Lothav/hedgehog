//
// Created by luiz0tavio on 5/6/18.
//

#ifndef BREAKOUT_TEXT_HPP
#define BREAKOUT_TEXT_HPP

#include <ft2build.h>
#include <GL/glew.h>
#include <memory>
#include FT_FREETYPE_H

namespace Renderer {


    class Text
    {
        float x_;
        float y_;
        float sx_;
        float sy_;
        FT_UInt size_;
        GLfloat color_[4];
        std::string text_;

        GLuint vbo_;

    public:

        Text(float x, float y, float sx, float sy, FT_UInt size, GLfloat color[4]);

        std::string getText();
        void setText(std::string text);

        float getX();
        float getY();

        float getSX();
        float getSY();

        FT_UInt getSize();

        GLfloat* getColor ();

        GLuint getVBO ();
    };
}


#endif //BREAKOUT_TEXT_HPP
