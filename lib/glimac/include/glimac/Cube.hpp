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

#define ATTR_POSITION_DEFAULT_LOC 0
#define ATTR_NORMAL_DEFAULT_LOC 1
#define ATTR_COLOUR_DEFAULT_LOC 2
#define ATTR_TEXCOORDS_DEFAULT_LOC 3

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
        union
        {
            ShapeVec3 _texCoords;
            ShapeVec3 _colour;
        };
    public:
        ShapeVertexCube(const ShapeVec3&  pos, const ShapeVec3& normal, const ShapeVec3& texCoords) :
                _position(pos), _normal(normal), _texCoords(texCoords) {}

        ShapeVertexCube(const ShapeVertexCube& shapeVertexCube) = default;
        ~ShapeVertexCube() = default;

        inline const ShapeVec3& getTexCoords() {return _texCoords;}
        inline void setTexCoords(const ShapeFloat x, const ShapeFloat y, const ShapeFloat z)
        {
            _texCoords.x = x;
            _texCoords.y = y;
            _texCoords.z = z;
        }
    };

    class AbstractCube
    {
    protected:
        std::vector<ShapeVertexCube> m_Vertices;
        std::vector<GLsizei> m_indexBuffer;
        GLsizei m_nVertexCount;
        GLsizei m_nIndexCount;
        GLuint _vbo, _ibo, _vao;
    public:
        AbstractCube(const GLfloat radius) :
            m_nVertexCount(CUBE_NB_VERTEX), m_nIndexCount(CUBE_NB_INDEX_BUFFER)
        {
            build(radius);
        }

        ~AbstractCube()
        {
            glDeleteVertexArrays(1, &_vao);
            glDeleteBuffers(1, &_ibo);
            glDeleteBuffers(1, &_vbo);
        }

        inline const ShapeVertexCube* getDataPointer() const {return m_Vertices.data();}
        inline const GLsizei* getIndexPointer() const {return m_indexBuffer.data();}

        inline GLsizei getVertexCount() const {return m_nVertexCount;}

    private:
        virtual void build(const GLfloat radius);
        virtual void buildVBO(const GLfloat radius) = 0;
        void buildIBO();

        void bind(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL, const GLuint ATTR_THIRD);
        void bindVBO();
        void bindIBO();
        void bindVAO(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL, const GLuint ATTR_THIRD);

        virtual void draw() const = 0;
    };

    class ColouredCube final : protected AbstractCube
    {
    public:
        ColouredCube(const GLfloat radius) : AbstractCube(radius) {}
        ~ColouredCube() {};
    private:
        void build(const GLfloat radius, const ShapeVec3& colour);
        void buildVBO(const GLfloat radius, const ShapeVec3& colour);

        void draw() const override {}
    };

    class TexturedCube final : protected  AbstractCube
    {
    public:
        TexturedCube(const GLfloat radius) : AbstractCube(radius)
        {
            //should be done by AbstractCube constructor
            //build(radius);
        }

        ~TexturedCube()
        {
            //Should be done by AbstractCube destructor
            /*
            glDeleteVertexArrays(1, &_vao);
            glDeleteBuffers(1, &_ibo);
            glDeleteBuffers(1, &_vbo);
             */
        }

    private:
        void buildVBO(const GLfloat radius) override;

        void draw() const override {}

    };
}
#endif //GLIMAC_CUBE_HPP
