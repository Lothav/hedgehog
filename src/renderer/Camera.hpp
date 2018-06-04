//
// Created by luiz0tavio on 6/4/18.
//

#ifndef HEDGEHOG_CAMERA_HPP
#define HEDGEHOG_CAMERA_HPP

#include <GL/glew.h>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

namespace Renderer
{
    class Camera
    {

    private:

        glm::mat4 view_camera_;
        GLuint shader_view_pos_;

    public:

        Camera(GLuint shader_program)
        {
            auto loc = glGetUniformLocation(shader_program, "view");
            if (loc < 0) std::cerr << "Can't find 'view' uniform on shader!" << std::endl;
            this->shader_view_pos_ = static_cast<GLuint>(loc);
        }

        void update(bool fixed)
        {
            if (fixed) {
                auto fixed_cam = glm::mat4();
                glUniformMatrix4fv(this->shader_view_pos_, 1, GL_FALSE, &fixed_cam[0][0]);
            } else {
                glUniformMatrix4fv(this->shader_view_pos_, 1, GL_FALSE, &this->view_camera_[0][0]);
            }
        }

        void move(glm::vec3 direction)
        {
            this->view_camera_ = glm::translate(this->view_camera_, direction);
        }

    };
}



#endif //HEDGEHOG_CAMERA_HPP
