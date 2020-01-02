//
// Created by piptouque on 27/11/2019.
//

#ifndef GLIMAC_CUBE_HPP
#define GLIMAC_CUBE_HPP

#pragma once

#include <vector>
#include <cstddef>

#include "common.hpp"
#include "Pattern.hpp"

#include <iostream>



#define CUBE_GEOMETRY_NB_VERTEX 8
#define CUBE_NB_VERTICES 3*CUBE_GEOMETRY_NB_VERTEX
#define CUBE_NB_INDICES_BUFFER ((3*CUBE_NB_VERTICES)/2)

namespace glimac
{

    ///brief: a Cube structure for VBO, IBO and VAO
    /// WIll be either textured or coloured..
    class CubePattern final : public Pattern
    {
    private:
        //In case of Coloured Cubes, the vertices do not have a third attribute.
        std::vector<ShapeVertexCube> m_Vertices;
    public:
        CubePattern(const GLfloat radius) : Pattern(CUBE_NB_VERTICES, CUBE_NB_INDICES_BUFFER),  m_Vertices(m_nVertexCount)
        {
            build(radius);
            bind(ATTR_POSITION_DEFAULT_LOC, ATTR_NORMAL_DEFAULT_LOC);
        }
        ~CubePattern() = default;

        inline const ShapeVertexCube* getDataPointer() const {return m_Vertices.data();}
    private:
        void build(const GLfloat radius);
        void buildVBO(const GLfloat radius);
        void buildVBOLoop(const GLfloat radius, const GLsizei x, const GLsizei y, const GLsizei z, const GLsizei offPos);
        void buildVBOAssign(const size_t vertexIndex, const ShapeVec3& position, const ShapeVec3& normal) ;
        void buildIBO();


        void bind(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL) const;
        void bindVBO() const override;
        void bindVAO(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL) const;
    };


}
#endif //GLIMAC_CUBE_HPP
