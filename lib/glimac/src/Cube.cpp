//
// Created by piptouque on 27/11/2019.
//

#include "glimac/Cube.hpp"

namespace glimac
{
    void AbstractCube::build(const GLfloat radius)
    {
        this->buildVBO(radius);
        this->buildIBO();
    }

    void ColouredCube::bind(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL) const
    {
        this->bindVBO();
        this->bindIBO();
        this->bindVAO(ATTR_POSITION, ATTR_NORMAL);
    }

    void TexturedCube::bind(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL, const GLuint ATTR_TEXCOORDS) const
    {
        this->bindVBO();
        this->bindIBO();
        this->bindVAO(ATTR_POSITION, ATTR_NORMAL, ATTR_TEXCOORDS);
    }

   void AbstractCube::buildVBO(const GLfloat radius)
   {
       /* offset for (x,y,z) positions */
       GLsizei offPos = CUBE_GEOMETRY_NB_VERTEX/3;
       /*Vertex assignment */
       for( GLsizei x=0; x<offPos;++x )
       {
           //todo: clean up this mess
           for( GLsizei y=0; y<offPos; ++y)
           {
               for( GLsizei z=0; z<offPos; ++z )
                    this->buildVBOLoop(radius, x, y, z, offPos);
           }

       }
   }


   void AbstractCube::buildVBOLoop(const GLfloat radius, const GLsizei x, const GLsizei y, const GLsizei z, const GLsizei offPos)
   {
       ShapeVec3 position = radius*ShapeVec3( x , y , z );
       /* need to get vertices three times
        * to account for different normals and texCoords
        */
       for( GLsizei i=0; i<3; ++i )
       {
           //todo: explain this
           ShapeVec3 rightDir = ShapeVec3(
                   (x < offPos/2)*2 - 1,
                   (y < offPos/2)*2 - 1,
                   (z < offPos/2)*2 - 1
           );
           ShapeVec3 normal = ShapeVec3(
                   (i%3)*rightDir.x,
                   ((i+1)%3)*rightDir.y,
                   ((i+2)%3)*rightDir.z
           );
           //We use the normal vector as texture coordinates.
           size_t totalIndex = i+3*(z+offPos*(y+offPos*x));
           this->buildVBOAssign(totalIndex, position, normal);
       }
   }

   void TexturedCube::buildVBOAssign(const GLsizei vertexIndex, const ShapeVec3& position, const ShapeVec3& normal)
   {
        //We are coosing the normal as the texture coordinates
       m_Vertices.at(vertexIndex) = ShapeVertexTextured(
               position,
               normal,
               normal
       );
   }

    void ColouredCube::buildVBOAssign(const GLsizei vertexIndex, const ShapeVec3& position, const ShapeVec3& normal)
    {
        //We are choosing the normal as the texture coordinates
        m_Vertices.at(vertexIndex) = ShapeVertexColoured(
                position,
                normal
        );
    }


   void AbstractCube::buildIBO() {
       /*
       GLsizei i=0;
       for(auto& indexBuffer : m_indexBuffer)
       {

       }
       */
       //todo: FACTOR THIS
       std::vector<GLsizei> &ibo = m_indexBuffer;
       /*FRONT FACE*/
       //lower-left half
       ibo[0] = 0; //x=0, y=0, z=0, i=0
       ibo[1] = 3;//x=0, y=0, z=1, i=0
       ibo[2] = 6;//x=0, y=1, z=0, i=0
       //upper-right half
       ibo[3] = 9;//x=0, y=1, z=1, i=0
       ibo[4] = 6;//x=0, y=1, z=0, i=0
       ibo[5] = 3;//x=0, y=0, z=1, i=0
       /*LEFT FACE*/
       //lower-right half
       ibo[6] = 1;//x=0, y=0, z=0, i=1
       ibo[7] = 4;//x=0, y=0, z=1, i=1
       ibo[8] = 13;//x=1, y=0, z=0, i=1
       //upper-left half
       ibo[9] = 13; //w=
       ibo[10] = 16;
       ibo[11] = 4;//x=1, y=0, z=1, i=1
       /*BOTTOM FACE*/
       //upper-left half
       ibo[12] = 2;//x=0, y=0, z=0, i=2
       ibo[13] = 14;//x=1, y=0, z=0, i=2
       ibo[14] = 8;//x=0, y=1, z=0, i=2
       //lower-right half
       ibo[15] = 8;//
       ibo[16] = 14;//
       ibo[17] = 20;//x=1, y=1, z=0, i=2
       /** HERE MIRROR X, Y AND Z AXIS **/
       /*FRONT FACE*/
       //lower-right half
       ibo[18] = 21;//x=1, y=1, z=1, i=0
       ibo[19] = 18;//x=1, y=1, z=0, i=0
       ibo[20] = 15;//x=1, y=0, z=1, i=0
       //upper-left half
       ibo[21] = 15;//
       ibo[22] = 18;//
       ibo[23] = 12;//x=1, y=0, z=0, i=0
       /*LEFT FACE*/
       //lower-right half
       ibo[24] = 22;//x=1, y=1, z=1, i=1
       ibo[25] = 19;//x=1, y=1, z=0, i=1
       ibo[26] = 10;//x=0, y=1, z=1, i=1
       //upper-left half
       ibo[27] = 10;//
       ibo[28] = 19;//
       ibo[29] = 7;//x=0,y=1, z=0, i=1
       /*BOTTOM FACE*/
       //upper-left half
       ibo[30] = 23;//x=1, y=1, z=1, i=2
       ibo[31] = 11;//x=0, y=1, z=1, i=2
       ibo[32] = 17;//x=1, y=0, z=1, i=2
       //lower-right half
       ibo[33] = 17;//
       ibo[34] = 11;//
       ibo[35] = 5;//x=0, y=0, z=1, i=2
   }
   void TexturedCube::bindVBO() const
   {
        //vbo is generated in AbstractCube constructor
       glBindBuffer(GL_ARRAY_BUFFER, _vbo); //VBO target
       glBufferData(
               GL_ARRAY_BUFFER,
               m_nVertexCount*sizeof(ShapeVertexTextured),
               this->getDataPointer(),
               GL_STATIC_DRAW //vertices are not expected to change
       );
       glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

    void ColouredCube::bindVBO() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo); //VBO target
        glBufferData(
                GL_ARRAY_BUFFER,
                m_nVertexCount*sizeof(ShapeVertexColoured),
                this->getDataPointer(),
                GL_STATIC_DRAW //vertices are not expected to change
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void AbstractCube::bindIBO() const
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

   void TexturedCube::bindVAO(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL, const GLuint ATTR_TEXTURE) const
   {
       glBindVertexArray(_vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
                glEnableVertexAttribArray(ATTR_POSITION);
                glEnableVertexAttribArray(ATTR_NORMAL);
                glEnableVertexAttribArray(ATTR_TEXTURE);
                glBindBuffer(GL_ARRAY_BUFFER, _vbo);
                    glVertexAttribPointer(
                        ATTR_POSITION,
                        3, //3 fields -> (x,y,z) we work in 3D
                        GL_FLOAT,
                        GL_FALSE, //not normalised
                        sizeof(ShapeVertexTextured),
                        (const GLfloat *) offsetof(ShapeVertexTextured, _position)
                        );
                    glVertexAttribPointer(
                        ATTR_NORMAL,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(ShapeVertexTextured),
                        (const GLfloat *) offsetof(ShapeVertexTextured, _normal)
                        );
                    glVertexAttribPointer(
                        ATTR_TEXTURE,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(ShapeVertexTextured),
                        (const GLfloat *) offsetof(ShapeVertexTextured, _texCoords) //or _colour, does not matter here
                        );
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
       glBindVertexArray(0);
   }

    void ColouredCube::bindVAO(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL) const
    {
        glBindVertexArray(_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glEnableVertexAttribArray(ATTR_POSITION);
        glEnableVertexAttribArray(ATTR_NORMAL);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glVertexAttribPointer(
                ATTR_POSITION,
                3, //3 fields -> (x,y,z) we work in 3D
                GL_FLOAT,
                GL_FALSE, //not normalised
                sizeof(ShapeVertexColoured),
                (const GLfloat *) offsetof(ShapeVertexColoured, _position)
        );
        glVertexAttribPointer(
                ATTR_NORMAL,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(ShapeVertexColoured),
                (const GLfloat *) offsetof(ShapeVertexColoured, _normal)
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void AbstractCube::draw() const
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



}