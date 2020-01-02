//
// Created by piptouque on 31/12/2019.
//

#ifndef WORLD_IMAKER_PATTERN_HPP
#define WORLD_IMAKER_PATTERN_HPP

#pragma once

#include <vector>
#include <cstddef>

#include "common.hpp"

#define ATTR_POSITION_DEFAULT_LOC 0
#define ATTR_NORMAL_DEFAULT_LOC 1
#define ATTR_TEXCOORDS_DEFAULT_LOC 2

#define QUAD_DEFAULT_OFFSET_VERTICES 2

namespace glimac
{
    class Pattern
    {
    protected:
        GLsizei m_nVertexCount;
        GLsizei m_nIndexCount;
        std::vector<GLsizei> m_indexBuffer;

        GLuint _vbo, _ibo, _vao;
    public:
        Pattern(GLsizei nbVertices, GLsizei nbIndices) :
                m_nVertexCount(nbVertices), m_nIndexCount(nbIndices),  m_indexBuffer(m_nIndexCount, 0), _vbo(), _ibo(), _vao()
        {
            glGenBuffers(1, &_vbo);
            glGenBuffers(1, &_ibo);
            glGenVertexArrays(1, &_vao);
            //actual building handled by child classes

        }

        ~Pattern()
        {
            glDeleteVertexArrays(1, &_vao);
            glDeleteBuffers(1, &_ibo);
            glDeleteBuffers(1, &_vbo);
        }

        inline const GLsizei* getIndexPointer() const {return m_indexBuffer.data();}

        inline GLsizei getVertexCount() const {return m_nVertexCount;}

    protected:
        virtual void bindVBO() const = 0;
        void bindIBO() const;

    public:
        void draw() const;
    };
}
#endif //WORLD_IMAKER_PATTERN_HPP
