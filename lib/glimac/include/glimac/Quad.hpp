//
// Created by piptouque on 31/12/2019.
//

#ifndef WORLD_IMAKER_QUAD_HPP
#define WORLD_IMAKER_QUAD_HPP

#pragma once

#include <vector>

#include "common.hpp"
#include "Pattern.hpp"

#define QUAD_NB_VERTICES 4
#define QUAD_NB_INDICES_BUFFER 6

namespace glimac
{
    class QuadPattern final : public Pattern
    {
    private:
        //In case of Coloured Cubes, the vertices do not have a third attribute.
        std::vector<ShapeVertexQuad> m_Vertices;
    public:
        QuadPattern(const ShapeVec2& centre, const GLfloat radius) : Pattern(QUAD_NB_VERTICES, QUAD_NB_INDICES_BUFFER),  m_Vertices(m_nVertexCount)
        {
            build(centre, radius);
            bind(ATTR_POSITION_DEFAULT_LOC, ATTR_TEXCOORDS_DEFAULT_LOC);
        }
        ~QuadPattern() = default;

        inline const ShapeVertexQuad* getDataPointer() const {return m_Vertices.data();}
    private:
        void build(const ShapeVec2& centre, const GLfloat radius);
        void buildVBO(const ShapeVec2& centre, const GLfloat radius);
        void buildIBO();


        void bind(const GLuint ATTR_POSITION, const GLuint ATTR_TEXCOORDS) const;
        void bindVBO() const override;
        void bindVAO(const GLuint ATTR_POSITION, const GLuint ATTR_TEXCOORDS) const;
    };
}
#endif //WORLD_IMAKER_QUAD_HPP
