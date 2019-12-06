//
// Created by piptouque on 27/11/2019.
//

#include "glimac/Cube.hpp"

namespace glimac
{
   //todo: refactor the two functions below

   void TexturedCube::buildVBO(const GLfloat radius)
   {
       /* offset for (x,y,z) positions */
       GLsizei offPos = CUBE_NB_VERTEX/3;
       /*Vertex assignment */
       for( GLsizei x=0; x<offPos;++x )
       {
           //todo: clean up this mess
           for( GLsizei y=0; y<offPos; ++y)
           {
               for( GLsizei z=0; z<offPos; ++z )
               {
                   ShapeVec3 position = radius*ShapeVec3( x % offPos, y % offPos, z % offPos );
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
                       m_Vertices.at(i+3*(z+offPos*(y+offPos*x))) = ShapeVertexCube(
                               position,
                               normal,
                              normal
                       );

                   }

               }
           }

       }
   }

   void ColouredCube::buildVBO(const GLfloat radius, const ShapeVec3& colour) {
       /* offset for (x,y,z) positions */
       GLsizei offPos = CUBE_NB_VERTEX / 3;
       /*Vertex assignment */
       for (GLsizei x = 0; x < offPos; ++x) {
           //todo: clean up this mess
           for (GLsizei y = 0; y < offPos; ++y) {
               for (GLsizei z = 0; z < offPos; ++z) {
                   ShapeVec3 position = radius * ShapeVec3(x % offPos, y % offPos, z % offPos);
                   /* need to get vertices three times
                    * to account for different normals and texCoords
                    */
                   for (GLsizei i = 0; i < 3; ++i) {
                       //todo: explain this
                       ShapeVec3 rightDir = ShapeVec3(
                               (x < offPos / 2) * 2 - 1,
                               (y < offPos / 2) * 2 - 1,
                               (z < offPos / 2) * 2 - 1
                       );
                       ShapeVec3 normal = ShapeVec3(
                               (i % 3) * rightDir.x,
                               ((i + 1) % 3) * rightDir.y,
                               ((i + 2) % 3) * rightDir.z
                       );
                       //We use the given colour vector
                       m_Vertices.at(i + 3 * (z + offPos * (y + offPos * x))) = ShapeVertexCube(
                               position,
                               normal,
                               colour
                       );

                   }

               }
           }
       }
   }

   void AbstractCube::buildIBO()
   {
       /*
       GLsizei i=0;
       for(auto& indexBuffer : m_indexBuffer)
       {

       }
       */
        //todo: FACTOR THIS
       std::vector<GLsizei>& ibo = m_indexBuffer;
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
       ibo[10] = 4;
       ibo[11] = 16;//x=1, y=0, z=1, i=1
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
       ibo[18]= 21;//x=1, y=1, z=1, i=0
       ibo[19]= 18;//x=1, y=1, z=0, i=0
       ibo[20]= 15;//x=1, y=0, z=1, i=0
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

   void AbstractCube::bindVBO()
   {
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo); //VBO target
            glBufferData(
                    GL_ARRAY_BUFFER,
                    m_nVertexCount*sizeof(ShapeVertexCube),
                    this->getDataPointer(),
                    GL_STATIC_DRAW //vertices are not expected to change
            );
        glBindBuffer(GL_ARRAY_BUFFER, 0);
   }

   void AbstractCube::bindIBO()
   {
       glGenBuffers(1, &_ibo);
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo); //IBO Target
            glBufferData(
                    GL_ELEMENT_ARRAY_BUFFER,
                    m_nIndexCount,
                    this->getIndexPointer(),
                    GL_STATIC_DRAW
            );
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   }

   void AbstractCube::bindVAO(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL, const GLuint ATTR_THIRD)
   {
       glGenVertexArrays(1, &_vao);
       glBindVertexArray(_vao);
            glEnableVertexAttribArray(ATTR_POSITION);
            glEnableVertexAttribArray(ATTR_NORMAL);
            glEnableVertexAttribArray(ATTR_THIRD);
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
                //ATTR_THIRD is either ATTR_COLOUR or ATTR_TEXCOORDS
                glVertexAttribPointer(
                        ATTR_THIRD,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(ShapeVertexCube),
                        (const GLfloat *) offsetof(ShapeVertexCube, _texCoords) //or _colour, does not matter here
                        );
            glBindBuffer(GL_ARRAY_BUFFER, 0);
       glBindVertexArray(0);
   }

   void AbstractCube::draw() const
   {
        glBindVertexArray(_vao);
            glDrawElements(
                    GL_TRIANGLES,
                    m_nVertexCount,
                    GL_UNSIGNED_INT,
                    this->getIndexPointer()
                    );
        glBindVertexArray(0);
   }

   void AbstractCube::build(const GLfloat radius)
   {
       //todo (with IBO)
       //VBO first
        this->buildVBO(radius);
        this->buildIBO();
   }

   void AbstractCube::bind(const GLuint ATTR_POSITION, const GLuint ATTR_NORMAL, const GLuint ATTR_THIRD)
   {
       this->bindVBO();
       this->bindIBO();
       this->bindVAO(ATTR_POSITION, ATTR_NORMAL, ATTR_THIRD);
   }


}