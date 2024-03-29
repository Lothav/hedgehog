//
// Created by luiz0tavio on 5/6/18.
//

#include "Text.hpp"

Renderer::Text::Text(float x, float y, FT_UInt size, GLfloat color[4]) : size_(size), text_("") ,vbo_()
{
    this->x_ = x;
    this->y_ = y;

    this->color_[0] = color[0];
    this->color_[1] = color[1];
    this->color_[2] = color[2];
    this->color_[3] = color[3];

    glGenBuffers(1, &this->vbo_);
}

void * Renderer::Text::operator new (std::size_t size)
{
    return Memory::Provider::getMemory(Memory::PoolType::POOL_TYPE_GENERIC, size);
}

void Renderer::Text::operator delete (void* ptr, std::size_t size) {}

std::string Renderer::Text::getText()
{
    return this->text_;
}

void Renderer::Text::setText(std::string text)
{
    this->text_ = std::move(text);
}

float Renderer::Text::getX()
{
    return this->x_;
}

float Renderer::Text::getY()
{
    return this->y_;
}

FT_UInt Renderer::Text::getSize()
{
    return this->size_;
}

GLfloat* Renderer::Text::getColor ()
{
    return this->color_;
}

GLuint Renderer::Text::getVBO ()
{
    return this->vbo_;
}