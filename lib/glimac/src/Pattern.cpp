//
// Created by piptouque on 31/12/2019.
//

#include "../include/glimac/Pattern.hpp"

namespace glimac
{
    void Pattern::draw() const
    {
        glBindVertexArray(_vao);
        glDrawElements(
                GL_TRIANGLES,
                m_nIndexCount,
                GL_UNSIGNED_INT,
                this->getIndexPointer()
        );
        glBindVertexArray(0);
    }

    void Pattern::bindIBO() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo); //IBO Target
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                m_nIndexCount*sizeof(GLsizei),
                this->getIndexPointer(),
                GL_STATIC_DRAW
        );
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}