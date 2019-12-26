//
// Created by piptouque on 18/12/2019.
//

#ifndef WORLD_IMAKER_LIGHT_HPP
#define WORLD_IMAKER_LIGHT_HPP

#include <vector>

#include "CommunDisplay.hpp"

#include "Randomisable.hpp"
#include "Listener.hpp"
#include "Exception.hpp"

#include "Types.hpp"
#include "Vec3D.hpp"
#include "Colour.hpp"

#pragma once

namespace wim {

    ///brief: constant in order to limit the number of lights.
    static const unsigned int MAX_NB_EACH_LIGHT = 10;

    static const glm::vec3 DEFAULT_AMBIANT_INTENSITY = {0.1, 0, 0};

    struct AmbiantLight
    {
    protected:
        Colour _intensity;
    public:
        AmbiantLight() : _intensity(DEFAULT_AMBIANT_INTENSITY) {}
        AmbiantLight(const Colour& intensity) :
                _intensity(intensity)
        {
        }

        inline const Colour& intensity() const {return _intensity;}
        inline Colour& intensity() {return _intensity;}
        static AmbiantLight Random();

    };
    ///brief: Data structure for SSBO
    struct PointLight final : public AmbiantLight
    {
    private:
        Vec3D _origin;
    public:
        PointLight(const Colour& intensity, const Vec3D& origin):
           AmbiantLight(intensity),_origin(origin) {}
        PointLight(const AmbiantLight& ambiant, const Vec3D& origin):
                AmbiantLight(ambiant),_origin(origin) {}

           inline const Vec3D& origin() const {return _origin;}

        inline Vec3D& origin() {return _origin;}

        static PointLight Random();
    };

    struct DirectionalLight final : public AmbiantLight
    {
    private:
        Vec3D _direction;
    public:
        DirectionalLight(const Colour& intensity, const Vec3D& direction):
                AmbiantLight(intensity), _direction(direction){}
        DirectionalLight(const AmbiantLight& ambiant, const Vec3D& direction):
                AmbiantLight(ambiant), _direction(direction){}


        inline const Vec3D& direction() const {return _direction;}
        inline Vec3D& direction() {return _direction;}


        static DirectionalLight Random();
    };


    typedef std::vector<PointLight> ListPLight;
    typedef std::vector<DirectionalLight> ListDLight;

    class LightManager : public Listenable
    {
    public:
        /* We use vectors to store lights
         * in order to use its consecutive memory storage
         * We also set a maximum number of each lights
         * So no problem of reallocation; we'll reserve enough space at init.
         */
    private:
        ListPLight _listPoint;
        ListDLight _listDirectional;
        AmbiantLight _ambiant;

    public:
        LightManager();

        void addPoint(const PointLight& pLight);
        void addDir(const DirectionalLight& dLight);

        void removePoint(const size_t index);
        void removeDir(const size_t index);

        inline const AmbiantLight& ambiant() const {return _ambiant;}
        inline AmbiantLight& ambiant() {return _ambiant;}

        inline const ListPLight& listPoint() const {return _listPoint;}
        inline ListPLight& listPoint() {return _listPoint;}

        inline const ListDLight& listDirectional() const {return _listDirectional;}
        inline ListDLight& listDirectional() {return _listDirectional;}


    };


    typedef std::unique_ptr<LightManager> LightManagerPtr;
}

#endif //WORLD_IMAKER_LIGHT_HPP
