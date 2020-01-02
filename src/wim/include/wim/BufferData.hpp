//
// Created by piptouque on 01/01/2020.
//

#ifndef WORLD_IMAKER_BUFFERDATA_HPP
#define WORLD_IMAKER_BUFFERDATA_HPP

#pragma once

#include <vector>

#include "CommonDisplay.hpp"
#include "Types.hpp"


#include "Material.hpp"
#include "Light.hpp"

namespace wim
{
    /* SEE STD140 FOR DETAILS ON OFFSETS AND SIZES
     * AS HANDLED BY GLSL
     */
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
       * of the two SSBO, apparently I'm not the only one with this issue:
       * https://gamedev.stackexchange.com/questions/96224/opengl-shader-storage-buffer-objects-array-length-problem
       * sending the sizes as a different SSBO is a fine work-around.
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
}

#endif //WORLD_IMAKER_BUFFERDATA_HPP
