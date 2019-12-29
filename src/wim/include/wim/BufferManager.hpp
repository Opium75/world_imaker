//
// Created by piptouque on 24/12/2019.
//

#ifndef WORLD_IMAKER_BUFFERMANAGER_HPP
#define WORLD_IMAKER_BUFFERMANAGER_HPP

#pragma once

#include <vector>
#include <memory>

#include "CommunDisplay.hpp"

#include "ShaderSender.hpp"
#include "TextureManager.hpp"
#include "BufferObject.hpp"

#include "Material.hpp"
#include "Light.hpp"
#include "Types.hpp"

namespace wim
{

    typedef std::unique_ptr<glimac::SDLWindowManager> WindowManagerPtr;

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
        glm::vec3 _colour;
        GLfloat _isTextured; //used as boolean
        glm::vec4 _kD;
        glm::vec3 _kS;
        GLfloat _shininess;
        MaterialData(const Material& material, const bool isTextured) :
            _colour(material.colour().getCoord()), _isTextured(isTextured), _kD(material.kD().getCoord(),0), _kS(material.kS().getCoord()), _shininess(material.shininess())
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

    /** NOTE: I can't get the shaders to recognise the sizes
       * of the two SSBO, apparently I(m not the only one with this issue:
       * https://gamedev.stackexchange.com/questions/96224/opengl-shader-storage-buffer-objects-array-length-problem
       * Anyway, sending the sizes as a different SSBO is a fine work-around.
       * **/
    struct LightNumberData
    {
        GLint _nbPoints;
        GLint _nbDirs;
        LightNumberData(const GLint nbPoints, const GLint nbDirs) :
            _nbPoints(nbPoints), _nbDirs(nbDirs) {}

    };

    struct PointLightData
    {
        glm::vec4 _intensity;
        glm::vec4 _origin_ms;

        PointLightData(const PointLight& pLight) :
                _intensity(pLight.intensity().getCoord(),0.f), _origin_ms(pLight.origin().getCoord(),1.f)
                {}

        inline  const glm::vec4& origin() const {return _origin_ms;}
        inline  glm::vec4& origin() {return _origin_ms;}
    };
    struct DirectionLightData
    {
        glm::vec4 _intensity;
        glm::vec4 _direction_ms;

        DirectionLightData(const DirectionLight &dLight) :
                _intensity(dLight.intensity().getCoord(), 0), _direction_ms(dLight.direction().getCoord(),0.f)
        {}
        inline  const glm::vec4& direction() const {return _direction_ms;}
        inline  glm::vec4& direction() {return _direction_ms;}
    };

    typedef std::vector<PointLightData> ListPLightData;
    typedef std::vector<DirectionLightData> ListDLightData;

    static constexpr const GLsizeiptr DEFAULT_MATRICES_BUFFERSIZE = sizeof(CameraMatricesData);
    static constexpr const GLsizeiptr DEFAULT_MATERIAL_BUFFERSIZE = sizeof(MaterialData);
    static constexpr const GLsizeiptr DEFAULT_AMBIANTLIGHT_BUFFERSIZE = sizeof(AmbiantLightData);

    static constexpr  const GLsizeiptr DEFAULT_LIGHTNUMBER_BUFFERSIZE = sizeof(LightNumberData);
    static constexpr const GLsizeiptr DEFAULT_ONE_POINTLIGHT_BUFFERSIZE = sizeof(PointLightData);
    static constexpr const GLsizeiptr DEFAULT_ONE_DIRECTIONALLIGHT_BUFFERSIZE = sizeof(DirectionLightData);

    typedef std::vector<ITO> ListITO;
    typedef std::shared_ptr<ListITO> ListITOPtr;

    class BufferManager
    {
    public:
    private:
        ListITOPtr _itos;
        UBO _matrices, _material, _ambiantLight;
        Uniform _baseTexture;
        SSBO _pointLights, _directionLights;
        SSBO _lightNumber;
        IFO _frameBuffer;
    public:

        BufferManager(const TextureManagerPtr& textures, const WindowManagerPtr& windows) :
            _itos(std::make_shared<ListITO>(textures->getCubeMaps().size())),
            _matrices(DEFAULT_MATRICES_BUFFERSIZE),
            _material(DEFAULT_MATERIAL_BUFFERSIZE),
            _ambiantLight(DEFAULT_AMBIANTLIGHT_BUFFERSIZE),
            _baseTexture(),
            _pointLights(DEFAULT_ONE_POINTLIGHT_BUFFERSIZE, MAX_NB_EACH_LIGHT),
            _directionLights(DEFAULT_ONE_DIRECTIONALLIGHT_BUFFERSIZE, MAX_NB_EACH_LIGHT),
            _lightNumber(DEFAULT_LIGHTNUMBER_BUFFERSIZE,1),
            _frameBuffer(windows->window(), NB_DEFAULT_DRAWBUFFERS, DEFAULT_DRAWBUFFERS)
        {
            this->loadCubeMaps(textures->getCubeMaps());
        }
        ~BufferManager() = default;


        ///brief; update MV, MVP, Normal and View matrices to shaders
        void updateMatrices(const UniformMatrix& MV, const UniformMatrix& Proj ) const;
        void updateMaterial(const Material& material, const bool isTextured) const;
        void updateLights(const LightManager& lights, const UniformMatrix& View ) const;
        void bindShaders(const ListSender& shaders) const;
        void localiseUniform(const ShaderSender& shader);

        void loadCubeMaps(const ListCubeMap& cubeMaps) const;

        inline ListITOPtr& getListITO() {return _itos;}

    private:
        void updateAmbiantLight(const AmbiantLight& ambiant) const;
        void updateLightNumber(const ListPLight& pLights, const ListDLight& dLights) const;
        void updatePointLights(const ListPLight& pLights, const UniformMatrix& View) const;
        void updateDirectionLights(const ListDLight& dLights, const UniformMatrix& View) const;

        void loadCubeMap(const SizeInt indexTexture, const CubeMap& cubeMap) const;
        void loadFace(const SizeInt indexFace, const SizeInt indexTexture, const CubeMap& cubeMap) const;

        void bindShader(const ShaderSender& shader) const;
    };

    typedef std::unique_ptr<BufferManager> BufferManagerPtr;
}

#endif //WORLD_IMAKER_BUFFERMANAGER_HPP
