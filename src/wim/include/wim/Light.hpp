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

    struct AmbiantLight
    {
    private:
        Colour _colour;
        GLfloat  _intensity;
    public:
        AmbiantLight() : _colour(Colour(DEFAULT_AMBIANT_COLOUR)), _intensity(DEFAULT_AMBIANT_INTENSITY) {}
        AmbiantLight(const Colour& colour, const GLfloat intensity) :
                _colour(colour), _intensity(intensity)
        {
        }

        inline const Colour& colour() const {return _colour;}
        inline Colour& colour() {return _colour;}
        inline GLfloat intensity() const {return _intensity;}
        inline GLfloat intensity() {return _intensity;}

    };
    ///brief: Data structure for SSBO
    struct PointLight final : public AmbiantLight
    {
        Vec3D _origin;
        PointLight(const Colour& colour, const GLfloat intensity, const Vec3D& origin):
           AmbiantLight(colour, intensity),_origin(origin)
            {

            }
    };

    struct DirectionalLight final : public AmbiantLight
    {
        Vec3D _direction;
        DirectionalLight(const Colour& colour, const GLfloat intensity, const Vec3D& direction):
                AmbiantLight(colour, intensity), _direction(direction)
        {

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
        typedef std::vector<PointLight> ListPLight;
        typedef std::vector<DirectionalLight> ListDLight;
    private:
        ListPLight _listPoint;
        ListDLight _listDir;
        AmbiantLight _ambiant;
        GLuint _ssboP, _ssboD;

    public:
        LightManager();
        LightManager(const AmbiantLight& ambiant) : _ambiant(ambiant) {}
        ~LightManager();
        inline void addPoint(const PointLight& pLight) {_listPoint.push_back(pLight);}
        inline void addDir(const DirectionalLight& dLight) {_listDir.push_back(dLight);}

        inline void removePoint(const size_t index) {_listPoint.erase(_listPoint.begin()+index);}
        inline void removeDir(const size_t index) {_listDir.erase(_listDir.begin()+index);}

        inline const AmbiantLight& getAmbiantLight() const {return _ambiant;}



    };


    typedef std::unique_ptr<LightManager> LightManagerPtr;
}

#endif //WORLD_IMAKER_LIGHT_HPP
