//
// Created by luiz0tavio on 6/2/18.
//

#include "Object2D.hpp"

Renderer::Object2D::Object2D(Position position, Size size, bool fixed) : fixed_(fixed), pos_(position), size_(size), vbo_(0), vertices_({}), texture_id_(0)
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

void Renderer::Object2D::setTexture(const std::string& path, const GLenum format)
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

GLuint Renderer::Object2D::getTextureId()
{
    return this->texture_id_;
}

GLuint Renderer::Object2D::getVBO()
{
    return this->vbo_;
}

std::array<GLfloat, SIZE_VERTICES> Renderer::Object2D::getVertices()
{
    return this->vertices_;
};

void * Renderer::Object2D::operator new (std::size_t size)
{
    return Memory::Provider::getMemory(Memory::PoolType::POOL_TYPE_GENERIC, size);
}