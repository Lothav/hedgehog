//
// Created by luiz0tavio on 6/2/18.
//

#ifndef BREAKOUT_BULKOBJECT2D_HPP
#define BREAKOUT_BULKOBJECT2D_HPP

#include <memory>
#include "Object2D.hpp"
#include "Shader.hpp"

namespace Renderer
{
    class BulkObject2D
    {
    public:

        static BulkObject2D& getInstance();

        BulkObject2D(BulkObject2D const&) = delete;
        void operator=(BulkObject2D const&)  = delete;

    private:

        std::vector<std::weak_ptr<Object2D>, Memory::Allocator<std::weak_ptr<Object2D>> > objects2d_;

        Renderer::Shader* shader_;
        GLuint shader_tex_pos_;
        GLuint shader_view_pos_;

        GLuint VBO;
        GLuint VAO;

        BulkObject2D();

    public:

        void push_back(const std::weak_ptr<Object2D>& object2d);

        void draw(std::array<int, 2> window_size);
    };
}

#endif //BREAKOUT_BULKOBJECT2D_HPP
