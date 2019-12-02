//
// Created by piptouque on 27/11/2019.
//

#ifndef GLIMAC_CUBE_HPP
#define GLIMAC_CUBE_HPP

#pragma once

#include <vector>
#include <cstddef>
#include "common.hpp"

#define CUBE_GEOMETRY_NB_VERTEX 8
#define CUBE_NB_VERTEX 3*CUBE_GEOMETRY_NB_VERTEX
#define CUBE_NB_INDEX_BUFFER (3*CUBE_NB_VERTEX)/2

namespace glimac
{

    /*Can't inherit from ShapeVertex
     * because it looks like it makes this class a non-standard
     * and thus offsetoff() does not work
     * Can we fix this ?
     */
    struct ShapeVertexCube
    {
    public:
        /* Will be using 3D textures for cubes,
         * Easier to handle this way,
         */
        ShapeVec3 _position;
        ShapeVec3 _normal;
        ShapeVec3 _texCoords;
    public:
        ShapeVertexCube(const ShapeVec3&  pos, const ShapeVec3& normal, const ShapeVec3& texCoords) :
                _position(pos), _normal(normal), _texCoords(texCoords) {}
                /* hides same method from hapeVertex */
        inline const ShapeVec3& getTexCoords() {return _texCoords;}
        inline void setTexCoords(const ShapeFloat x, const ShapeFloat y, const ShapeFloat z)
        {
            _texCoords.x = x;
            _texCoords.y = y;
            _texCoords.z = z;
        }
    };

    class Cube
    {
    private:
        std::vector<ShapeVertexCube> m_Vertices;
        std::vector<GLsizei> m_indexBuffer;
        GLsizei m_nVertexCount;
        GLsizei m_nIndexCount;

    public:
        Cube(const GLfloat radius) : m_nVertexCount(CUBE_NB_VERTEX), m_nIndexCount(CUBE_NB_INDEX_BUFFER)
        {
            build(radius);
        }

       inline const ShapeVertexCube* getDataPointer() const {return m_Vertices.data();}
       inline const GLsizei* getIndexPointer() const {return m_indexBuffer.data();}

       inline GLsizei getVertexCount() const {return m_nVertexCount;}

    private:
        void build(const GLfloat radius);
        void buildVBO(const GLfloat radius);
        void buildIBO();

        void bind(GLuint &vbo, GLuint &ibo, GLuint &vao, const GLuint ATTR_POSITION=0, const GLuint ATTR_NORMAL=1, const GLuint ATTR_TEXCOORDS=2) const;
        void bindVBO(GLuint &vbo) const;
        void bindIBO(GLuint &ibo) const;
        void bindVAO(GLuint &vao, const GLuint vbo, const GLuint ATTR_POSITION=0, const GLuint ATTR_NORMAL=1, const GLuint ATTR_TEXCOORDS=2) const;

        void draw(const GLuint vao) const;
    };
}
#endif //GLIMAC_CUBE_HPP
