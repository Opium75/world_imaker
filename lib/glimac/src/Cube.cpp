//
// Created by piptouque on 27/11/2019.
//

#include "glimac/Cube.hpp"

namespace glimac
{
    void CubePattern::build(const GLfloat radius)
    {
        this->buildVBO(radius);
        this->buildIBO();
    }

    void CubePattern::bind(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL) const
    {
        this->bindVBO();
        this->bindIBO();
        this->bindVAO(ATTR_POSITION, ATTR_NORMAL);
    }

   void CubePattern::buildVBO(const GLfloat radius)
   {
       /* offset for (x,y,z) positions */
       GLsizei offPos = QUAD_DEFAULT_OFFSET_VERTICES;
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


   void CubePattern::buildVBOLoop(const GLfloat radius, const GLsizei x, const GLsizei y, const GLsizei z, const GLsizei offPos)
   {
        //Centring the Cube on origin.
       ShapeVec3 position = radius*ShapeVec3( (x-(offPos-1.f)/2.f),( y-(offPos-1.f)/2.f) , (z - (offPos-1.f)/2.f));
       /* need to get vertices three times
        * to account for different normals and texCoords
        */
       //todo: explain this
       ShapeVec3 rightDir = ShapeVec3(
               (x >= offPos/2)*2 - 1,
               (y >= offPos/2)*2 - 1,
           (z >= offPos/2)*2 - 1
       );
       for( GLsizei i=0; i<3; ++i )
       {
           ShapeVec3 normal = ShapeVec3(
                   (i == 0)*rightDir.x,
                   (i == 1)*rightDir.y,
                   (i == 2)*rightDir.z
           );
           //We use the normal vector as texture coordinates.
           size_t totalIndex = i+3*(z+offPos*(y+offPos*x));
           this->buildVBOAssign(totalIndex, position, normal);
       }
   }


    void CubePattern::buildVBOAssign(const size_t vertexIndex, const ShapeVec3& position, const ShapeVec3& normal)
    {
        //We are choosing the normal as the texture coordinates
        m_Vertices.at(vertexIndex) = ShapeVertexCube(
                position,
                normal
        );
    }


   void CubePattern::buildIBO() {

       //todo: FACTOR THIS
       auto &ibo = m_indexBuffer;
        /*
         *
         *     (1,1,1) ______________(0,1,1)    y
        *             | \(1,1,0)______\(0,1,0)  ^
        *             |  |            |         |
        *             |  |            |         |
        *        (1,0,1)_|_____(0,0,1)|         |
        *               \|          \ |
        * <--x   (1,0,0)  \ __________\ (0,0,0)
        *
        */
       /*FRONT FACE*/  //normal : (0,0,-1) -> i=2
       //lower-right half
       ibo[0] = 2; //x=0, y=0, z=0
       ibo[1] = 8;//x=0, y=1, z=0
       ibo[2] = 14;//x=1, y=0, z=0
       //upper-left half
       ibo[3] = 20;//x=1, y=1, z=0
       ibo[4] = 14;//x=1, y=0, z=0
       ibo[5] = 8;//x=0, y=1, z=0
       /*RIGHT FACE*/ //normal : (-1, 0, 0) -> i=0
       //lower-left half
       ibo[6] = 0;//x=0, y=0, z=0
       ibo[7] = 6;//x=0, y=1, z=0
       ibo[8] = 3;//x=0, y=0, z=1
       //upper-right half
       ibo[9] = 9; //x=0, y=1, z=1
       ibo[10] = 3;
       ibo[11] = 6;
       /*BOTTOM FACE*/ //normal : (0, -1, 0) -> i = 1
       //lower-right half
       ibo[12] = 1;//x=0, y=0, z=0
       ibo[13] = 13;//x=1, y=0, z=0
       ibo[14] = 4;//x=0, y=, z=1
       //upper-left half
       ibo[15] = 16;//(1,0,1)
       ibo[16] = 4;//
       ibo[17] = 13;//
       /** HERE MIRROR X, Y AND Z AXIS **/
       /*
         *
         *     (0,0,0) ______________(1,0,0)    -y
        *             | \(0,0,1)______\(1,0,1)  ^
        *             |  |            |         |
        *             |  |            |         |
        *        (0,1,0)_|_____(1,1,0)|         |
        *               \|          \ |
        *<--(-x)(0,1,1)  \ __________\|(1,1,1)
        *
        */
       /*FRONT FACE*/ //normal : (0,0,1) -> i=2
       //lower-right half
       ibo[18] = 23;//x=1, y=1, z=1
       ibo[19] = 17;//x=1, y=0, z=1
       ibo[20] = 11;//x=0, y=1, z=1
       //upper-left half
       ibo[21] = 5;//(0,0,1)
       ibo[22] = 11;//
       ibo[23] = 17;//
       /*RIGHT FACE*/ //normal : (1,0,0) -> i=0
       //lower-left half
       ibo[24] = 21;//x=1, y=1, z=1
       ibo[25] = 15;//x=1, y=0, z=1
       ibo[26] = 18;//x=1, y=1, z=0
       //upper-right half
       ibo[27] = 12;//(1,0,0)
       ibo[28] = 18;//
       ibo[29] = 15;//
       /*BOTTOM FACE*/ //normal : (0,1,0) -> i=1
       //lower-right half
       ibo[30] = 22;//x=1, y=1, z=1
       ibo[31] = 19;//x=1, y=1, z=0
       ibo[32] = 10;//x=0, y=1, z=1
       //upper-left half
       ibo[33] = 7;//(0,1,0)
       ibo[34] = 10;//
       ibo[35] = 19;//
   }
    void CubePattern::bindVBO() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo); //VBO target
        glBufferData(
                GL_ARRAY_BUFFER,
                m_nVertexCount*sizeof(ShapeVertexCube),
                this->getDataPointer(),
                GL_STATIC_DRAW //vertices are not expected to change
        );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }



    void CubePattern::bindVAO(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL) const
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
                                sizeof(ShapeVertexCube),
                                (const GLfloat *) offsetof(ShapeVertexCube, _position)
                        );
                        glVertexAttribPointer(
                                ATTR_NORMAL,
                                3,
                                GL_FLOAT,
                                GL_FALSE,
                                sizeof(ShapeVertexCube),
                                (const GLfloat *) offsetof(ShapeVertexCube, _normal)
                        );
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }





}