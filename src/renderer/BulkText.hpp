//
// Created by luiz0tavio on 5/27/18.
//

#ifndef BREAKOUT_BULKTEXT_HPP
#define BREAKOUT_BULKTEXT_HPP

#include <vector>
#include "Text.hpp"
#include "Shader.hpp"

namespace Renderer {

    class BulkText
    {

    public:

        static BulkText& getInstance();

        BulkText(BulkText const&) = delete;
        void operator=(BulkText const&)  = delete;

    private:

        std::vector<Text *, Memory::Allocator<Text *> > texts_;

        Renderer::Shader* shader_;
        GLuint shader_tex_pos_;
        GLuint shader_coord_pos_;
        GLuint shader_color_pos_;

        FT_Face freetype_face_;

        BulkText();

    public:

        void * operator new (std::size_t size);

        void  operator delete (void* ptr, std::size_t) {}

        void push_back(Text* text);

        void draw(std::array<int, 2> window_size);

    };
}



#endif //BREAKOUT_BULKTEXT_HPP
