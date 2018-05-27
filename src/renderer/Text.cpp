//
// Created by luiz0tavio on 5/6/18.
//

#include "Text.hpp"

Renderer::Text::Text(float x, float y, float sx, float sy, FT_Face font_face) : x_(x), y_(y), sx_(sx), sy_(sy),font_face_(font_face), vbo()
{
    this->shader = new Renderer::Shader();
    this->shader->createGraphicShader(GL_VERTEX_SHADER, "text.vert");
    this->shader->createGraphicShader(GL_FRAGMENT_SHADER, "text.frag");
    this->shader->link();

    GLint loc;

    loc = glGetUniformLocation(this->shader->getShaderProgram(), "tex");
    if (loc < 0) {
        std::cerr << "Can't find 'tex' uniform on shader!" << std::endl;
    }
    this->uniform_tex_ = static_cast<GLuint>(loc);

    loc = glGetAttribLocation(this->shader->getShaderProgram(), "coord");
    if (loc < 0) {
        std::cerr << "Can't find 'coord' attr on shader!" << std::endl;
    }
    this->attribute_coord_ = static_cast<GLuint>(loc);

    loc = glGetUniformLocation(this->shader->getShaderProgram(), "color");
    if (loc < 0) {
        std::cerr << "Can't find 'color' uniform on shader!" << std::endl;
    }
    this->uniform_color_ = static_cast<GLuint>(loc);

    glGenBuffers(1, &this->vbo);
}

void Renderer::Text::prepare(FT_UInt font_size=48)
{
    this->shader->use();
    GLfloat black[4] = { 1, 1, 1, 1 };

    /* Set font size to 48 pixels, color to black */
    FT_Set_Pixel_Sizes(this->font_face_, 0, font_size);
    glUniform4fv(this->uniform_color_, 1, black);
}

void Renderer::Text::draw(std::string text)
{
    FT_GlyphSlot g = this->font_face_->glyph;

    /* Create a texture that will be used to hold one "glyph" */
    GLuint tex;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(this->uniform_tex_, 0);

    /* We require 1 byte alignment when uploading texture data */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /* Clamping to edges is important to prevent artifacts when scaling */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    /* Linear filtering usually looks best for text */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Set up the VBO for our vertex data */
    glEnableVertexAttribArray(this->attribute_coord_);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glVertexAttribPointer(this->attribute_coord_, 4, GL_FLOAT, GL_FALSE, 0, 0);

    auto x_tmp = this->x_;
    auto y_tmp = this->y_;

    /* Loop through all characters */
    for (char i : text) {
        /* Try to load and render the character */
        if (FT_Load_Char(this->font_face_, i, FT_LOAD_RENDER))
            continue;

        /* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

        /* Calculate the vertex and texture coordinates */
        float x2 = x_tmp + g->bitmap_left * sx_;
        float y2 = -y_tmp - g->bitmap_top * sy_;
        float w  = g->bitmap.width * sx_;
        float h  = g->bitmap.rows * sy_;

        point box[4] = {
                {    x2,     -y2, 0, 0},
                {x2 + w,     -y2, 1, 0},
                {    x2, -y2 - h, 0, 1},
                {x2 + w, -y2 - h, 1, 1},
        };

        /* Draw the character on the screen */
        glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        /* Advance the cursor to the start of the next character */
        x_tmp += (g->advance.x >> 6) * this->sx_;
        y_tmp += (g->advance.y >> 6) * this->sy_;
    }

    glDisableVertexAttribArray(this->attribute_coord_);
    glDeleteTextures(1, &tex);
}