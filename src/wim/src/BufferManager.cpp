//
// Created by piptouque on 24/12/2019.
//

#include "../include/wim/BufferManager.hpp"

namespace wim
{


    void BufferManager::bindShader(const ShaderSender& shader) const {
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

        //POINT AND DIRECTIONAL LIGHTS
        _pointLights.bind(shader.programme().getGLId(),
                          STORAGE_BLOCK_POINTLIGHT_NAME,
                          BINDING_POINTLIGHT_INDEX
        );
        _directionalLights.bind(shader.programme().getGLId(),
                                STORAGE_BLOCK_DIRECTIONALLIGHT_NAME,
                                BINDING_DIRECTIONALLIGHT_INDEX
        );
    }

    void BufferManager::updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj) const
    {

        CameraMatricesData data(MV, Proj);
        _matrices.update(&data, sizeof(data));
    }

    void BufferManager::updateMaterial(const Material& material) const
    {
        MaterialData data(material);
        _material.update(&data, sizeof(MaterialData));
    }

    void BufferManager::updateLights(const LightManager &lights) const
    {
        this->updateAmbiantLight(lights.ambiant());
        this->updatePointLights(lights.listPoint());
        this->updateDirectionalLights(lights.listDirectional());
    }

    void BufferManager::updateAmbiantLight(const AmbiantLight &ambiant) const
    {
        AmbiantLightData data(ambiant);
        _ambiantLight.update(&data, sizeof(AmbiantLightData));
    }

    void BufferManager::updatePointLights(const ListPLight& pLights) const
    {
        ListPLightData data(pLights.begin(), pLights.end());
        _pointLights.update(data.data(), sizeof(PointLightData), data.size());

    }
    void BufferManager::updateDirectionalLights(const ListDLight& dLights) const
    {
        ListDLightData data(dLights.begin(), dLights.end());
        _directionalLights.update(data.data(), sizeof(DirectionalLightData), data.size());
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
                     nullptr,
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

    void SSBO::alloc(const GLsizeiptr size, const SizeInt max) const
    {
        //We have to allocate enough memory
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
            glBufferData(GL_SHADER_STORAGE_BUFFER,
                     size*max,
                     nullptr,
                     GL_DYNAMIC_COPY
            );
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void SSBO::bind(const GLuint programme, const char* storageBufferName, const GLuint binding) const
    {
        this->bindBlock(programme, storageBufferName, binding);
        this->bindObject(binding);
    }

    void SSBO::bindObject(const GLuint binding) const
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, _ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void SSBO::bindBlock(const GLuint programme, const char* storageBufferName, const GLuint binding) const
    {
        GLuint index = glGetProgramResourceIndex(programme, GL_SHADER_STORAGE_BLOCK, storageBufferName);
        glShaderStorageBlockBinding(programme, index, binding);
    }

    void SSBO::update(const GLvoid* data, const GLsizeiptr size, const SizeInt nbUpdate) const
    {
        GLvoid *bufferPtr;
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
            bufferPtr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
                std::memcpy(bufferPtr,
                    data,
                    size*nbUpdate);
            glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        //todo: Check if unbinding here is a mistake.
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }
}