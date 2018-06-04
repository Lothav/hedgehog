//
// Created by luiz0tavio on 6/2/18.
//

#ifndef BREAKOUT_BULKOBJECT2D_HPP
#define BREAKOUT_BULKOBJECT2D_HPP

#include <memory>
#include "Object2D.hpp"
#include "Shader.hpp"
#include <glm/mat4x4.hpp> // glm::vec4

namespace Renderer
{
    class BulkObject2D
    {
    public:

        static BulkObject2D& getInstance();

        BulkObject2D(BulkObject2D const&) = delete;
        void operator=(BulkObject2D const&)  = delete;

    private:

        std::vector<Object2D *, Memory::Allocator<Object2D *> > objects2d_;

        Renderer::Shader* shader_;
        GLuint shader_tex_pos_;
        GLuint shader_uv_pos_;
        GLuint shader_view_pos_;
        GLuint shader_vert_pos_;

        glm::mat4 view_camera_;

        BulkObject2D();

    public:

        void * operator new (std::size_t size);

        void  operator delete (void* ptr, std::size_t) {}

        void push_back(Object2D * object2d);

        void draw();
    };
}

#endif //BREAKOUT_BULKOBJECT2D_HPP
