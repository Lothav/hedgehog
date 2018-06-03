//
// Created by luiz0tavio on 6/2/18.
//

#include "BulkObject2D.hpp"

Renderer::BulkObject2D &Renderer::BulkObject2D::getInstance()
{
    static Renderer::BulkObject2D instance;
    return instance;
}

Renderer::BulkObject2D::BulkObject2D() : objects2d_({}), shader_(nullptr), view_camera_(glm::mat4())
{
    // Compile/Link/Set Shader Program
    this->shader_ = new Renderer::Shader();
    this->shader_->createGraphicShader(GL_VERTEX_SHADER, "default.vert");
    this->shader_->createGraphicShader(GL_FRAGMENT_SHADER, "default.frag");
    this->shader_->link();

    auto loc = glGetUniformLocation(this->shader_->getShaderProgram(), "tex");
    if (loc < 0) std::cerr << "Can't find 'tex' uniform on shader!" << std::endl;
    this->shader_tex_pos_ = static_cast<GLuint>(loc);

    loc = glGetUniformLocation(this->shader_->getShaderProgram(), "view");
    if (loc < 0) std::cerr << "Can't find 'view' uniform on shader!" << std::endl;
    this->shader_view_pos_ = static_cast<GLuint>(loc);

    loc = glGetAttribLocation(this->shader_->getShaderProgram(), "vert");
    if (loc < 0) std::cerr << "Error find location Attribute shader!" << std::endl;
    this->shader_vert_pos_ = static_cast<GLuint>(loc);

    loc = glGetAttribLocation(this->shader_->getShaderProgram(), "vertTexCoord");
    if (loc < 0) std::cerr << "Error find location Attribute shader!" << std::endl;
    this->shader_uv_pos_ = static_cast<GLuint>(loc);
}

void Renderer::BulkObject2D::push_back(const std::weak_ptr<Object2D>& object2d)
{
    this->objects2d_.push_back(object2d);
}

void Renderer::BulkObject2D::draw()
{
    this->shader_->use();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnableVertexAttribArray(this->shader_vert_pos_);
    glEnableVertexAttribArray(this->shader_uv_pos_);

    for (const auto &object2d : objects2d_) {

        auto object2d_ptr = object2d.lock();
        if (!object2d_ptr) {
            std::cerr << "Object2D pointer not valid!" << std::endl;
            continue;
        }

        GLsizei stride = COORDINATES_BY_VERTEX*sizeof(GLfloat);
        glBindBuffer(GL_ARRAY_BUFFER, object2d_ptr->getVBO());
        glVertexAttribPointer(this->shader_vert_pos_, 3, GL_FLOAT, GL_TRUE, stride, nullptr);
        glVertexAttribPointer(this->shader_uv_pos_, 2, GL_FLOAT, GL_TRUE, stride, (const GLvoid*)(3 * sizeof(GLfloat)));

        auto texture_id = object2d_ptr->getTextureId();
        glActiveTexture(GL_TEXTURE0 + texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glUniform1i(this->shader_tex_pos_, texture_id);

        glUniformMatrix4fv(this->shader_view_pos_, 1, GL_FALSE, &this->view_camera_[0][0]);

        auto vertices = object2d_ptr->getVertices();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
    }

}