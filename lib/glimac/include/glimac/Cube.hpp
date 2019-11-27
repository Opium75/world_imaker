//
// Created by piptouque on 27/11/2019.
//

#ifndef GLIMAC_CUBE_HPP
#define GLIMAC_CUBE_HPP

#pragma once

#include<vector>
#include "common.hpp"

namespace glimac
{
    class Cube
    {
    private:
        std::vector<ShapeVertex> m_Vertices;
        GLsizei m_nVertexCount;

    public:
        Cube(const GLfloat radius) : m_nVertexCount(0)
        {
            build(radius);
        }

       inline const ShapeVertex* getDataPointer() const {return &m_Vertices[0];}

       inline GLsizei getVertexCount() const {return m_nVertexCount;}

    private:
        void build(const GLfloat radius);
    };
}
#endif //GLIMAC_CUBE_HPP
