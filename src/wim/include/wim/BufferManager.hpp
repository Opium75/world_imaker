//
// Created by piptouque on 24/12/2019.
//

#ifndef WORLD_IMAKER_BUFFERMANAGER_HPP
#define WORLD_IMAKER_BUFFERMANAGER_HPP

#pragma once

#include "CommunDisplay.hpp"
#include "ShaderSender.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "Types.hpp"

namespace wim
{


    /*Names of uniform attributs as they are used in the shaders
     * For now, we will only support one light source. IN POINT LIGHT
     */
    //MATRICES
    static constexpr const char* UNI_BLOCK_MATRICES_NAME = "bMatrices";
    //MATERIAL
    static constexpr const char* UNI_BLOCK_MATERIAL_NAME = "bMaterial";
    /* LIGHTs
     * One ambiant, and multiple point and directional lights
     * (using shader storage buffers; see Light.hpp for storage details.)
     */
    static constexpr const char* UNI_BLOCK_AMBIANTLIGHT_NAME = "bAmbiantLight";
    /* SEE STD140 FOR DETAILS ON OFFSETS AND SIZES
     * AS HANDLED BY GLSL
     */

    static const GLuint BINDING_MATRICES_INDEX = 0;
    static const GLuint BINDING_MATERIAL_INDEX = 1;
    static const GLuint BINDING_AMBIANTLIGHT_INDEX = 2;
    static const GLuint BINDING_POSLIGHT_INDEX = 3;
    static const GLuint BINDING_DIRLIGHT_INDEX = 4;

    //todo: find a way to get required sizes
    static const GLsizeiptr DEFAULT_MATRICES_BUFFERSIZE = 3*sizeof(UniformMatrix);
    static const GLsizeiptr DEFAULT_MATERIAL_BUFFERSIZE = 3*sizeof(Material);
    static const GLsizeiptr DEFAULT_AMBIANTLIGHT_BUFFERSIZE = 3*sizeof(AmbiantLightData);


    struct UBO
    {
    public:
        GLuint _ubo;
    public:
        UBO() : _ubo()
        {
            glGenBuffers(1, &_ubo);

        }
        ~UBO()
        {
            glDeleteBuffers(1,&_ubo);
        }


        void bindBlock(const GLuint programme, const char* UNI_BUFFER_NAME, const GLuint binding) const
        {
            GLuint index = glGetUniformBlockIndex(programme, UNI_BUFFER_NAME);
            glUniformBlockBinding(programme, index, binding);
        }

        void bindObject(const GLuint binding) const
        {
            glBindBufferBase(GL_UNIFORM_BUFFER, binding, _ubo);
        }

        void alloc(const GLsizeiptr size) const
        {
            glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
            glBufferData(GL_UNIFORM_BUFFER,
                         size,
                         NULL,
                         GL_DYNAMIC_DRAW
            );
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }



        void update(const GLvoid* data, const GLsizeiptr offset,  const GLsizeiptr size) const
        {
            glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
                glBufferSubData(GL_UNIFORM_BUFFER,
                                offset,
                                size,
                                data);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }
    };

    class BufferManager
    {
        UBO _matrices, _material, _ambiantLight;

    public:

        BufferManager() = default;
        ~BufferManager() = default;

        void updateMatrix(const UniformMatrix& M, SizeInt indexOffset) const
        {
            this->_matrices.update(glm::value_ptr(M), indexOffset*sizeof(UniformMatrix), sizeof(UniformMatrix));
        }

        void bindShader(const ShaderSender& shader) const;
        void allocAllUniBuffers() const;
        void bindAllUBO() const;

        void updateVec3Only(const UBO& object, const glm::vec3& vec, const SizeInt indexOffset) const;
        void updateFloatLast(const UBO& object, const GLfloat value, const SizeInt indexOffset) const;


        ///brief; update ModelView, ModevViewProjection (From Projection and ModelView), and Normal matrices to shaders
        void updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj) const;
        void updateMaterial(const Material& material) const;
        void updateAmbiantLight(const AmbiantLightData& ambiant) const;

        void init(const ListSender& shaders) const;
    };
}

#endif //WORLD_IMAKER_BUFFERMANAGER_HPP
