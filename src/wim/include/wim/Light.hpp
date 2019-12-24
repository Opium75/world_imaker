//
// Created by piptouque on 18/12/2019.
//

#ifndef WORLD_IMAKER_LIGHT_HPP
#define WORLD_IMAKER_LIGHT_HPP

#include <vector>

#include "CommunDisplay.hpp"

#include "Types.hpp"
#include "Vec3D.hpp"
#include "Colour.hpp"

#pragma once

namespace wim {

    ///brief: constant in order to limit the number of lights.
    static const unsigned int MAX_NB_EACH_LIGHTS = 10;

    static const GLfloat DEFAULT_AMBIANT_INTENSITY = 1.f;
    static const glm::vec3 DEFAULT_AMBIANT_COLOUR = {1.f, 1.f, 1.f};

    struct AmbiantLightData
    {
        glm::vec3 _colour;
        GLfloat  _intensity;
        AmbiantLightData() : _colour(DEFAULT_AMBIANT_COLOUR), _intensity(DEFAULT_AMBIANT_INTENSITY) {}
        AmbiantLightData(const glm::vec3& colour, const GLfloat intensity) :
                _colour(colour), _intensity(intensity)
        {
        }
    };
    ///brief: Data structure for SSBO
    struct PointLightData final : public AmbiantLightData
    {
        glm::vec3 _origin;
        PointLightData(const glm::vec3& colour, const GLfloat intensity, const glm::vec3& origin):
           AmbiantLightData(colour, intensity),_origin(origin)
            {

            }
    };

    struct DirectionalLightData final : public AmbiantLightData
    {
        glm::vec3 _direction;
        DirectionalLightData(const glm::vec3& colour, const GLfloat intensity, const glm::vec3& direction):
                AmbiantLightData(colour, intensity), _direction(direction)
        {

        }
    };

    class AmbiantLight {
    private:
        Colour _colour;
        FloatType _intensity;

    public:
        AmbiantLight() = default;
        AmbiantLight(const Colour& colour, const FloatType intensity) : _colour(colour), _intensity(intensity) {}
        ~AmbiantLight() = default;

        glm::vec3 getColourData() const {return _colour.getCoord();}
        GLfloat getIntensity() const {return _intensity;}
        inline AmbiantLightData getAmbiantSSBOData() const
        {
            return AmbiantLightData(this->getColourData(), this->getIntensity());
        }
    };

    class PointLight final : public AmbiantLight {

    private:
        Point3D _origin; //coordinates of the light in World.
    public:
        PointLight(const Colour& colour, const FloatType intensity, const Point3Int& origin) : AmbiantLight(colour, intensity), _origin(origin) {}

        glm::vec3 getOrigin() const {return _origin.getCoord();}

        inline PointLightData getSSBOData() const
        {
            return PointLightData(this->getColourData(),
                    this->getIntensity(),
                    this->getOrigin()
                    );
        }
    };

    class DirectionalLight final : public AmbiantLight {

    private:
        Vec3D _direction;
    public:
        DirectionalLight(const Colour& colour, const FloatType intensity, const Vec3D& direction) : AmbiantLight(colour, intensity), _direction(direction) {}

        glm::vec3 getDirection() const {return _direction.getCoord();}

        inline DirectionalLightData getSSBOData() const
        {
            return DirectionalLightData(this->getColourData(),
                             this->getIntensity(),
                             this->getDirection()
            );

        }
    };



    class LightManager
    {
    public:
        /* We use vectors to store lights
         * in order to use its consecutive memory storage
         * We also set a maximum number of each lights
         * So no problem of reallocation; we'll reserve enough space at init.
         */
        typedef std::vector<PointLightData> ListPLight;
        typedef std::vector<DirectionalLightData> ListDLight;
    private:
        ListPLight _listPoint;
        ListDLight _listDir;
        AmbiantLightData _ambiant;
        GLuint _ssboP, _ssboD;

    public:
        LightManager();
        LightManager(const AmbiantLightData& ambiant) : _ambiant(ambiant) {}
        ~LightManager();
        inline void addPoint(const PointLight& pLight) {_listPoint.push_back(pLight.getSSBOData());}
        inline void addDir(const DirectionalLight& dLight) {_listDir.push_back(dLight.getSSBOData());}

        inline void removePoint(const size_t index) {_listPoint.erase(_listPoint.begin()+index);}
        inline void removeDir(const size_t index) {_listDir.erase(_listDir.begin()+index);}

        inline const AmbiantLightData& getAmbiantLight() const {return _ambiant;}

        void buildSSBO() const;
        void updateSSBO() const;


        //todo: only update SSBOs when there is a change in lights.
        void update();

    };


    //Light Manager needs to be shared between Model and Scene Renderer
    typedef std::shared_ptr<LightManager> LightManagerPtr;
}

#endif //WORLD_IMAKER_LIGHT_HPP
