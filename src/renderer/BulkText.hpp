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

        static BulkText& getInstance()
        {
            static BulkText instance;
            return instance;
        }

        BulkText(BulkText const&) = delete;
        void operator=(BulkText const&)  = delete;

    private:

        std::vector<std::weak_ptr<Text>> texts_;

        Renderer::Shader* shader_;
        GLuint shader_tex_pos_;
        GLuint shader_coord_pos_;
        GLuint shader_color_pos_;

        FT_Face freetype_face_;

        BulkText();

    public:

        void push_back(const std::weak_ptr<Text>& text);

        void draw();

    };
}



#endif //BREAKOUT_BULKTEXT_HPP
