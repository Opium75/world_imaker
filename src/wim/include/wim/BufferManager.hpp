//
// Created by piptouque on 24/12/2019.
//

#ifndef WORLD_IMAKER_BUFFERMANAGER_HPP
#define WORLD_IMAKER_BUFFERMANAGER_HPP

#pragma once

#include <vector>

#include "CommunDisplay.hpp"
#include "ShaderSender.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "Types.hpp"

namespace wim
{

    struct CameraMatricesData
    {
        UniformMatrix _MVP, _MV, _Normal;
        CameraMatricesData(const UniformMatrix& MV, const UniformMatrix& Proj) :
            _MVP(Proj*MV), _MV(MV), _Normal(glm::transpose(glm::inverse(MV)))
        {
        }
    };

    struct MaterialData
    {
        glm::vec4 _colour, _kD;
        glm::vec3 _kS;
        GLfloat _shininess;
        MaterialData(const Material& material) :
            _colour(material.colour().getCoord(),0), _kD(material.kD().getCoord(),0), _kS(material.kS().getCoord()), _shininess(material.shininess())
        {
        }
    };

    struct AmbiantLightData
    {
        glm::vec3 _intensity;
        AmbiantLightData(const AmbiantLight& ambiant):
           _intensity(ambiant.intensity().getCoord())
        {
        }
    };

    struct PointLightData
    {
        glm::vec4 _intensity;
        glm::vec3 _origin;

        PointLightData(const PointLight& pLight) :
                _intensity(pLight.intensity().getCoord(),0), _origin(pLight.origin().getCoord())
                {}
    };
    struct DirectionalLightData
    {
        glm::vec4 _intensity;
        glm::vec3 _direction;

        DirectionalLightData(const DirectionalLight &dLight) :
                _intensity(dLight.intensity().getCoord(), 0), _direction(dLight.direction().getCoord())
        {}
    };

    typedef std::vector<PointLightData> ListPLightData;
    typedef std::vector<DirectionalLightData> ListDLightData;

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

    static constexpr const char* STORAGE_BLOCK_POINTLIGHT_NAME = "sPointLight";
    static constexpr const char* STORAGE_BLOCK_DIRECTIONALLIGHT_NAME = "sDirectionalLight";
    /* SEE STD140 FOR DETAILS ON OFFSETS AND SIZES
     * AS HANDLED BY GLSL
     */

    static const GLuint BINDING_MATRICES_INDEX = 0;
    static const GLuint BINDING_MATERIAL_INDEX = 1;
    static const GLuint BINDING_AMBIANTLIGHT_INDEX = 2;
    static const GLuint BINDING_POINTLIGHT_INDEX = 3;
    static const GLuint BINDING_DIRECTIONALLIGHT_INDEX = 4;

    //todo: find a way to get required sizes
    static const GLsizeiptr GLSL_STD140_FLOAT = 4;//in bytes
    static const GLsizeiptr GLSL_STD140_VEC3 = 16;
    static const GLsizeiptr GLSL_STD140_MAT4 = 64;
    static const GLsizeiptr DEFAULT_MATRICES_BUFFERSIZE = sizeof(CameraMatricesData);
    static const GLsizeiptr DEFAULT_MATERIAL_BUFFERSIZE = sizeof(MaterialData);
    static const GLsizeiptr DEFAULT_AMBIANTLIGHT_BUFFERSIZE = sizeof(AmbiantLightData);

    static const GLsizeiptr DEFAULT_ONE_POINTLIGHT_BUFFERSIZE = sizeof(PointLightData);
    static const GLsizeiptr DEFAULT_ONE_DIRECTIONALLIGHT_BUFFERSIZE = sizeof(DirectionalLightData);


    struct UBO
    {
    public:
        GLuint _ubo;
    public:
        UBO(const GLsizeiptr size) : _ubo()
        {
            glGenBuffers(1, &_ubo);
            this->alloc(size);

        }
        ~UBO() {glDeleteBuffers(1,&_ubo);}


        void bind(const GLuint programme, const char* uniBufferName, const GLuint binding) const;
        void alloc(const GLsizeiptr size) const;
        void update(const GLvoid* data,  const GLsizeiptr size) const;
    private:
        void bindBlock(const GLuint programme, const char* uniBufferName, const GLuint binding) const;
        void bindObject(const GLuint binding) const;
    };

    struct SSBO
    {
    public:
        GLuint _ssbo;
    public:
        SSBO(const GLsizeiptr size, const SizeInt max) : _ssbo()
        {
            glGenBuffers(1, &_ssbo);
            this->alloc(size, max);
        }
        ~SSBO() {glDeleteBuffers(1, &_ssbo);}

        void alloc(const GLsizeiptr size, const SizeInt max) const;
        void bind(const GLuint programme, const char* storageBufferName, const GLuint binding) const;
        void update(const GLvoid* data, const GLsizeiptr size, const SizeInt nbUpdate) const;

    private:
        void bindObject(const GLuint binding) const;
        void bindBlock(const GLuint programme, const char* storageBufferName, const GLuint binding) const;

    };

    class BufferManager
    {
        UBO _matrices, _material, _ambiantLight;
        SSBO _pointLights, _directionalLights;
    public:

        BufferManager() :
            _matrices(DEFAULT_MATRICES_BUFFERSIZE),
            _material(DEFAULT_MATERIAL_BUFFERSIZE),
            _ambiantLight(DEFAULT_AMBIANTLIGHT_BUFFERSIZE),
            _pointLights(DEFAULT_ONE_POINTLIGHT_BUFFERSIZE, MAX_NB_EACH_LIGHT),
            _directionalLights(DEFAULT_ONE_DIRECTIONALLIGHT_BUFFERSIZE, MAX_NB_EACH_LIGHT)
        {

        }
        ~BufferManager() = default;


        ///brief; update modelview, modevviewprojection (from projection and modelview), and normal matrices to shaders
        void updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj) const;
        void updateMaterial(const Material& material) const;
        void updateLights(const LightManager& lights) const;
        void bindShaders(const ListSender& shaders) const;

    private:
        void updateAmbiantLight(const AmbiantLight& ambiant) const;
        void updatePointLights(const ListPLight& pLights) const;
        void updateDirectionalLights(const ListDLight& dLights) const;

        void bindShader(const ShaderSender& shader) const;

    };
}

#endif //WORLD_IMAKER_BUFFERMANAGER_HPP
