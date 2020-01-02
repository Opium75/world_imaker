//
// Created by piptouque on 31/12/2019.
//

#include "../include/glimac/Quad.hpp"

namespace glimac {
    void QuadPattern::build(const ShapeVec2& centre, const GLfloat radius) {
        this->buildVBO(centre, radius);
        this->buildIBO();
    }

    void QuadPattern::bind(const GLuint ATTR_POSITION, const GLuint ATTR_TEXCOORDS) const
    {
        this->bindVBO();
        this->bindIBO();
        this->bindVAO(ATTR_POSITION, ATTR_TEXCOORDS);
    }

    void QuadPattern::buildVBO(const ShapeVec2& centre, const GLfloat radius) {
        /* offset for (x,y) positions */
        GLsizei offPos = QUAD_DEFAULT_OFFSET_VERTICES;
        /*Vertex assignment */
        for (GLsizei x = 0; x < offPos; ++x)
        {
            for (GLsizei y = 0; y < offPos; ++y)
            {
                ShapeVec2 texCoords =ShapeVec2(x/(offPos-1.f), y/(offPos - 1.f));
                ShapeVec2 position = centre + radius *texCoords;
                m_Vertices.at(x * offPos + y) = ShapeVertexQuad(
                        position,
                        texCoords
                );
            }

        }
    }

    void QuadPattern::buildIBO() {

        auto &ibo = m_indexBuffer;
        /*
         *      (0,1)_______________ (1,1)
         *          |               |
         *          |               |
         *          |               |
         *          |               |
         *     (0,0)|_______________|(1,0)
         *
        */
        //lower-left half
        ibo[0] = 0; //x=0, y=0
        ibo[1] = 1;//x=1, y=0
        ibo[2] = 2;//x=0, y=1
        //upper-right half
        ibo[3] = 3;//x=1, y=1
        ibo[4] = 1;//x=1, y=0
        ibo[5] = 2;//x=0, y=1
    }

    void QuadPattern::bindVBO() const {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo); //VBO target
        glBufferData(
                GL_ARRAY_BUFFER,
                m_nVertexCount * sizeof(ShapeVertexQuad),
                this->getDataPointer(),
                GL_STATIC_DRAW //vertices are not expected to change
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }


    void QuadPattern::bindVAO(const GLuint ATTR_POSITION, const GLuint ATTR_TEXCOORDS) const
    {

        glBindVertexArray(_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glEnableVertexAttribArray(ATTR_POSITION);
        glEnableVertexAttribArray(ATTR_TEXCOORDS);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glVertexAttribPointer(
                ATTR_POSITION,
                2, //2 fields -> (x,y)
                GL_FLOAT,
                GL_FALSE, //not normalised
                sizeof(ShapeVertexQuad),
                (const GLfloat *) offsetof(ShapeVertexQuad, _position)
        );
        glVertexAttribPointer(
                ATTR_TEXCOORDS,
                2,
                GL_FLOAT,
                GL_FALSE,
                sizeof(ShapeVertexQuad),
                (const GLfloat *) offsetof(ShapeVertexQuad, _texCoords)
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}