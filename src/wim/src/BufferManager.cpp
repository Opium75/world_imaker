//
// Created by piptouque on 24/12/2019.
//

#include "../include/wim/BufferManager.hpp"

#include <string>
#include <algorithm>

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

        //POINT AND DIRECTIONAL LIGHTS
        _pointLights.bind(shader.programme().getGLId(),
                          STORAGE_BLOCK_POINTLIGHT_NAME,
                          BINDING_POINTLIGHT_INDEX
        );
        _directionLights.bind(shader.programme().getGLId(),
                                STORAGE_BLOCK_DIRECTIONLIGHT_NAME,
                                BINDING_DIRECTIONLIGHT_INDEX
        );

        _lightNumber.bind(shader.programme().getGLId(),
                            STORAGE_BLOCK_LIGHTNUMBER_NAME,
                            BINDING_LIGHTNUMBER_INDEX
                            );
    }

    void BufferManager::localiseUniform(const ShaderSender& shader)
    {
        //BASE TEXTURE
        _baseTexture.localise(shader.programme().getGLId(),
                              UNI_LOC_BASETEXTURE_NAME
        );
    }

    void BufferManager::updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj ) const
    {

        CameraMatricesData data(MV, Proj );
        _matrices.update(&data, sizeof(data));
    }

    void BufferManager::updateMaterial(const Material& material, const bool isTextured) const
    {
        MaterialData data(material, isTextured);
        _material.update(&data, sizeof(MaterialData));
    }

    void BufferManager::updateLights(const LightManager &lights, const UniformMatrix& View) const
    {
        this->updateAmbiantLight(lights.ambiant());
        this->updatePointLights(lights.listPoint(), View);
        this->updateDirectionLights(lights.listDirection(), View);
        this->updateLightNumber(lights.listPoint(), lights.listDirection());
    }

    void BufferManager::updateAmbiantLight(const AmbiantLight &ambiant) const
    {
        AmbiantLightData data(ambiant);
        _ambiantLight.update(&data, sizeof(AmbiantLightData));
    }

    void BufferManager::updatePointLights(const ListPLight& pLights, const UniformMatrix& View) const
    {
        ListPLightData data(pLights.begin(), pLights.end());
        //from model to view:
        std::for_each(data.begin(), data.end(),
                      [View](PointLightData& data) {data.origin() = View*data.origin();}
        );
        _pointLights.update(data.data(), sizeof(PointLightData), data.size() );

    }
    void BufferManager::updateDirectionLights(const ListDLight& dLights, const UniformMatrix& View) const
    {
        ListDLightData data(dLights.begin(), dLights.end());
        //from model to view:
        std::for_each(data.begin(), data.end(),
                [View](DirectionLightData &data) {data.direction() = View*data.direction();}
                );
        _directionLights.update(data.data(), sizeof(DirectionLightData), data.size() );
    }

    void BufferManager::updateLightNumber(const ListPLight &pLights, const ListDLight &dLights) const
    {
        LightNumberData data(pLights.size(), dLights.size());
        _lightNumber.update(&data, sizeof(LightNumberData), 1);
    }

    void BufferManager::bindShaders(const ListSender& shaders) const
    {
        for( const auto& shader : shaders )
        {
            this->bindShader(shader);
        }
    }

    void BufferManager::loadCubeMaps(const ListCubeMap &cubeMaps) const
    {
        SizeInt index = 0;
        std::for_each(cubeMaps.begin(), cubeMaps.end(),
                    [this, &index](const CubeMap& cubeMap)
                    {this->loadCubeMap(index++, cubeMap);}
        );
    }

    void BufferManager::loadCubeMap(const SizeInt indexTexture, const CubeMap& cubeMap) const
    {
        for(SizeInt indexFace=0; indexFace<cubeMap.getNumberFaces(); ++indexFace)
            this->loadFace(indexFace, indexTexture, cubeMap);
    }

    void BufferManager::loadFace(const SizeInt indexFace, const SizeInt indexTexture, const CubeMap& cubeMap) const
    {
        _itos->at(indexTexture).loadFace(
                indexFace,
                cubeMap.getPixels(indexFace),
                cubeMap.getWidth(indexFace),
                cubeMap.getHeight(indexFace)
        );
    }

    void UBO::bindObject(const GLuint binding) const
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, _ubo);
    }

    void UBO::bindBlock(const GLuint programme, const char* uniBufferName, const GLuint binding) const
    {
        GLuint index = glGetUniformBlockIndex(programme, uniBufferName);
        if( index == GL_INVALID_INDEX)
        {
            throw Exception(ExceptCode::ILLIGAL, 1,
                            std::string("In programme #") + std::to_string(programme)+
                            std::string(" Required block not found: ") + uniBufferName);
        }
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
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, _ssbo);
    }

    void SSBO::bindBlock(const GLuint programme, const char* storageBufferName, const GLuint binding) const
    {
        GLuint index = glGetProgramResourceIndex(programme, GL_SHADER_STORAGE_BLOCK, storageBufferName);
        if( index == GL_INVALID_INDEX )
        {
            throw Exception(ExceptCode::ILLIGAL, 1,
                    std::string("In programme #") + std::to_string(programme)+
                    std::string(" Required block not found: ") + storageBufferName);
        }
        glShaderStorageBlockBinding(programme, index, binding);
    }

    void SSBO::update(const GLvoid* data, const GLsizeiptr size, const SizeInt nbUpdate ) const
    {
        GLvoid *bufferPtr;
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
            bufferPtr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
                std::memcpy(bufferPtr,
                    data,
                    size*nbUpdate);
            glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void ITO::setParameters() const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _ito);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void ITO::loadFace(const SizeInt indexFace, GLvoid *data, const GLsizei width, const GLsizei height) const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _ito);
            glTexImage2D(
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X+indexFace,
                    0, //level of detail with regards to mipmap
                    GL_RGBA,
                    width,
                    height,
                    0, //border: alvays 0
                    GL_RGBA,
                    GL_FLOAT,
                    data
                    );
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        //
        this->setParameters();
        //glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }

    void Uniform::localise(const GLuint programme, const char *uniAttrName)
    {
        _uId = glGetUniformLocation(programme, uniAttrName);
        if( _uId == -1)
        {
            throw Exception(ExceptCode::ILLIGAL, 1,
                            std::string("In programme #") + std::to_string(programme) +
                            std::string(" Required uniform not found: ") + uniAttrName);
        }
    }

    void Uniform::update(const GLint texId) const
    {
    glUniform1i(_uId, texId);
    }
}