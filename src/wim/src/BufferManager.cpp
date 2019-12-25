//
// Created by piptouque on 24/12/2019.
//

#include "../include/wim/BufferManager.hpp"

namespace wim
{


    void BufferManager::bindShader(const ShaderSender& shader) const
    {
        //MATRICES
        _matrices.bind(shader.programme().getGLId(),
                                  UNI_BLOCK_MATRICES_NAME,
                                  BINDING_MATRICES_INDEX
        );
        //MATERIAL
        _material.bind(shader.programme().getGLId(),
                                  UNI_BLOCK_MATERIAL_NAME,
                                  BINDING_MATERIAL_INDEX
        );
        //AMBIANT LIGHT
        _ambiantLight.bind(shader.programme().getGLId(),
                                      UNI_BLOCK_AMBIANTLIGHT_NAME,
                                      BINDING_AMBIANTLIGHT_INDEX
        );
    }
/*
    void BufferManager::updateMatrix(const UniformMatrix& m, SizeInt indexOffset) const
    {
        this->_matrices.update(glm::value_ptr(m),
                indexOffset*GLSL_STD140_MAT4,
                sizeof(UniformMatrix));
    }

    void BufferManager::updateVec3Only(const UBO& object, const glm::vec3& vec, const SizeInt indexOffset) const
    {
        object.update(glm::value_ptr(vec),
                indexOffset*GLSL_STD140_VEC3,
                sizeof(glm::vec3));
    }

    void BufferManager::updateFloatLast(const UBO& object, const GLfloat value, const SizeInt indexOffset) const
    {
        object.update(&value,
                indexOffset*GLSL_STD140_VEC3,
                sizeof(GLfloat));
    }*/

    void BufferManager::updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj) const
    {

        CameraMatricesData data(MV, Proj);
        _matrices.update(&data, sizeof(data));
    }

    void BufferManager::updateMaterial(const Material& material) const
    {
        /*
        //colour
        this->updateVec3Only(_material, material.colour().getCoord(), 0);
        //ks et ks
        this->updateVec3Only(_material, material.kD().getCoord(), 1);
        this->updateVec3Only(_material, material.kS().getCoord(), 2);
        //shininess
        this->updateFloatLast(_material, material.shininess(), 3);
         */
        MaterialData data(material);
        _material.update(&data, sizeof(data));

    }

    void BufferManager::updateAmbiantLight(const AmbiantLight &ambiant) const
    {
        //colour
        /*this->updateVec3Only(_ambiantLight, ambiant._colour, 0);
        this->updateFloatLast(_ambiantLight, ambiant._intensity, 1);
         */
        AmbiantLightData data(ambiant);
        _ambiantLight.update(&data, sizeof(data));
    }

    void BufferManager::bindShaders(const ListSender& shaders) const
    {
        for( const auto& shader : shaders )
        {
            this->bindShader(shader);
        }
    }

    void UBO::bindObject(const GLuint binding) const
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, _ubo);
    }

    void UBO::bindBlock(const GLuint programme, const char* uniBufferName, const GLuint binding) const
    {
        GLuint index = glGetUniformBlockIndex(programme, uniBufferName);

        glUniformBlockBinding(programme, index, binding);
    }


    void UBO::bind(const GLuint programme, const char* uniBufferName, const GLuint binding) const
    {
        this->bindBlock(programme, uniBufferName, binding);
        this->bindObject(binding);
    }

    void UBO::alloc(const GLsizeiptr size) const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
        glBufferData(GL_UNIFORM_BUFFER,
                     size,
                     NULL,
                     GL_DYNAMIC_DRAW
        );
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UBO::update(const GLvoid* data, const GLsizeiptr size) const
    {
        /* Update everything in the structure */
        glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
          GLvoid *p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
                std::memcpy(p, data, size);
            glUnmapBuffer(GL_UNIFORM_BUFFER);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
}