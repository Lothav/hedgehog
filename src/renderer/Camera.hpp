//
// Created by luiz0tavio on 6/4/18.
//

#ifndef HEDGEHOG_CAMERA_HPP
#define HEDGEHOG_CAMERA_HPP

#include <GL/glew.h>
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <array>

namespace Renderer
{
    class Camera
    {

    private:

        glm::mat4 mvp_;

        glm::mat4 model_;
        glm::mat4 view_;
        glm::mat4 projection_;

        GLuint shader_view_pos_;

    public:

        Camera(GLuint shader_program, std::array<int, 2> window_default_size) : shader_view_pos_(0)
        {
            auto loc = glGetUniformLocation(shader_program, "view");
            if (loc < 0) std::cerr << "Can't find 'view' uniform on shader!" << std::endl;
            this->shader_view_pos_ = static_cast<GLuint>(loc);

            // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
            this->projection_ = glm::perspective(glm::radians(45.0f), (GLfloat)window_default_size[0] / (GLfloat)window_default_size[0], 0.1f, 100.0f);

            this->view_ = glm::lookAt(
                glm::vec3(0, 0, 1), // Camera is at (4,3,3), in World Space
                glm::vec3(0, 0, 0), // and looks at the origin
                glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
            );

            this->model_ = glm::mat4(1.0f);

            this->updateMVP();
        }

        void update(bool fixed)
        {
            if (fixed) {
                auto fixed_cam = glm::mat4();
                glUniformMatrix4fv(this->shader_view_pos_, 1, GL_FALSE, &fixed_cam[0][0]);
            } else {
                glUniformMatrix4fv(this->shader_view_pos_, 1, GL_FALSE, &this->mvp_[0][0]);
            }
        }

        void move(glm::vec3 direction)
        {
            this->view_ = glm::translate(this->view_, direction);
            this->updateMVP();
        }

    private:

        void updateMVP()
        {
            this->mvp_ = this->projection_ * this->view_ * this->model_;
        }

    };
}



#endif //HEDGEHOG_CAMERA_HPP
