//
// Created by luiz0tavio on 5/6/18.
//

#ifndef BREAKOUT_TEXT_HPP
#define BREAKOUT_TEXT_HPP

#include <ft2build.h>
#include <GL/glew.h>
#include <memory>
#include FT_FREETYPE_H
#include "Shader.hpp"

struct point {
    GLfloat x;
    GLfloat y;
    GLfloat s;
    GLfloat t;
};

namespace Renderer {


    class Text
    {
        float x_;
        float y_;
        float sx_;
        float sy_;
        FT_Face font_face_;

        GLuint vbo;

        GLuint uniform_tex_;
        GLuint attribute_coord_;
        GLuint uniform_color_;

        Renderer::Shader* shader;

    public:

        Text(float x, float y, float sx, float sy, FT_Face font_face);

        void prepare(FT_UInt font_size = 48);

        void draw(std::string text);

    };
}


#endif //BREAKOUT_TEXT_HPP
