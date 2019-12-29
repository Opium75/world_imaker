//
// Created by piptouque on 27/11/2019.
//

#ifndef GLIMAC_CUBE_HPP
#define GLIMAC_CUBE_HPP

#pragma once

#include <vector>
#include <cstddef>
#include "common.hpp"

#include <iostream>

#define CUBE_GEOMETRY_NB_VERTEX 8
#define CUBE_NB_VERTEX 3*CUBE_GEOMETRY_NB_VERTEX
#define CUBE_NB_INDEX_BUFFER (3*CUBE_NB_VERTEX)/2

#define ATTR_POSITION_DEFAULT_LOC 0
#define ATTR_NORMAL_DEFAULT_LOC 1
#define ATTR_TEXCOORDS_DEFAULT_LOC 3

namespace glimac
{

    class AbstractCube
    {
    protected:
        GLsizei m_nVertexCount;
        GLsizei m_nIndexCount;
        std::vector<GLsizei> m_indexBuffer;

        GLuint _vbo, _ibo, _vao;
    public:
        AbstractCube() :
            m_nVertexCount(CUBE_NB_VERTEX), m_nIndexCount(CUBE_NB_INDEX_BUFFER),  m_indexBuffer(m_nIndexCount, 0), _vbo(), _ibo(), _vao()
        {
            glGenBuffers(1, &_vbo);
            glGenBuffers(1, &_ibo);
            glGenVertexArrays(1, &_vao);
            //actual building handled by child classes

        }

        ~AbstractCube()
        {
            glDeleteVertexArrays(1, &_vao);
            glDeleteBuffers(1, &_ibo);
            glDeleteBuffers(1, &_vbo);
        }

        inline const GLsizei* getIndexPointer() const {return m_indexBuffer.data();}

        inline GLsizei getVertexCount() const {return m_nVertexCount;}

    protected:
        void build(const GLfloat radius);
        void buildVBO(const GLfloat radius);
        void buildVBOLoop(const GLfloat radius, const GLsizei x, const GLsizei y, const GLsizei z, const GLsizei offPos);
        virtual void buildVBOAssign(const GLsizei vertexIndex, const ShapeVec3& position, const ShapeVec3& normal)
        {
            //USE THESE PARAMETERS OR ELSE
            std::cout << vertexIndex << position << normal << std::endl;
        }
        void buildIBO();

        virtual void bindVBO() const  {};
        void bindIBO() const;

    public:
        void draw() const;
    };

    ///brief: a Cube structure for VBO, IBO and VAO
    /// WIll be either textured or coloured..
    class CubePattern final : public AbstractCube
    {
    private:
        //In case of Coloured Cubes, the vertices do not have a third attribute.
        std::vector<ShapeVertexCube> m_Vertices;
    public:
        CubePattern(const GLfloat radius) :  m_Vertices(m_nVertexCount)
        {
            build(radius);
            bind(ATTR_POSITION_DEFAULT_LOC, ATTR_NORMAL_DEFAULT_LOC);
        }
        ~CubePattern() = default;

        inline const ShapeVertexCube* getDataPointer() const {return m_Vertices.data();}
    private:
        void buildVBOAssign(const GLsizei vertexIndex, const ShapeVec3& position, const ShapeVec3& normal) override;

        void bind(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL) const;
        void bindVBO() const override;
        void bindVAO(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL) const;
    };


}
#endif //GLIMAC_CUBE_HPP
