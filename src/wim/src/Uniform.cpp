//
// Created by piptouque on 01/01/2020.
//

#include "../include/wim/Uniform.hpp"

namespace wim
{
    void UBO::bindObject(const GLuint binding) const
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, _id);
    }

    void UBO::bindBlock(const GLuint programme, const char* uniBufferName, const GLuint binding) const
    {
        GLuint index = glGetUniformBlockIndex(programme, uniBufferName);
        if( index == GL_INVALID_INDEX)
        {
            throw Exception(ExceptCode::ILLIGAL, 1,
                            std::string("In programme #") + std::to_string(programme)+
                            std::string(" Required block not found: ") + uniBufferName);
        }
        glUniformBlockBinding(programme, index, binding);
    }


    void UBO::bind(const GLuint programme, const char* uniBufferName, const GLuint binding) const
    {
        this->bindBlock(programme, uniBufferName, binding);
        this->bindObject(binding);
    }

    void UBO::alloc(const GLsizeiptr size) const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, _id);
        glBufferData(GL_UNIFORM_BUFFER,
                     size,
                     nullptr,
                     GL_DYNAMIC_DRAW
        );
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UBO::update(const GLvoid* data, const GLsizeiptr size) const
    {
        /* Update everything in the structure */
        glBindBuffer(GL_UNIFORM_BUFFER, _id);
        GLvoid *p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
        std::memcpy(p, data, size);
        glUnmapBuffer(GL_UNIFORM_BUFFER);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }




    void Uniform::localise(const GLuint programme, const char *uniAttrName)
    {
        _id = glGetUniformLocation(programme, uniAttrName);

        if( _id == -1)
         {
            /*
            throw Exception(ExceptCode::ILLIGAL, 1,
                             std::string("In programme #") + std::to_string(programme) +
                             std::string(" Required uniform not found: ") + uniAttrName);
             */
         }
    }


    void Uniform::updateCubeIndex(const Point3Uint& anchor) const
    {
        glUniform3uiv(_id,
                1,
                glm::value_ptr(anchor.getCoord())
                );
    }

}