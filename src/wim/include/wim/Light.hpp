//
// Created by piptouque on 18/12/2019.
//

#ifndef WORLD_IMAKER_LIGHT_HPP
#define WORLD_IMAKER_LIGHT_HPP

#include <vector>
#include <utility>

#include "CommonDisplay.hpp"

#include "Randomisable.hpp"
#include "Exception.hpp"

#include "Types.hpp"
#include "Vec3D.hpp"
#include "Colour.hpp"

#pragma once

namespace wim {

    ///brief: constant in order to limit the number of lights.
    static const unsigned int MAX_NB_EACH_LIGHT = 10;


    struct AmbiantLight
    {
    protected:
        Colour _intensity;
    public:
        AmbiantLight(const Colour& intensity) :
                _intensity(intensity)
        {
        }

        inline const Colour& intensity() const {return _intensity;}
        inline Colour& intensity() {return _intensity;}
        AmbiantLight& operator=(const AmbiantLight& ambiant);
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

       PointLight& operator=(const PointLight& pLight);

        static PointLight Random();
    };

    struct DirectionLight final : public AmbiantLight
    {
    private:
        Vec3D _direction;
    public:
        DirectionLight(const Colour& intensity, const Vec3D& direction):
                AmbiantLight(intensity), _direction(direction){}
        DirectionLight(const AmbiantLight& ambiant, const Vec3D& direction):
                AmbiantLight(ambiant), _direction(direction){}


        inline const Vec3D& direction() const {return _direction;}
        inline Vec3D& direction() {return _direction;}
        DirectionLight& operator=(const DirectionLight& dLight);

        static DirectionLight Random();
    };


    typedef std::vector<PointLight> ListPLight;
    typedef std::vector<DirectionLight> ListDLight;

    class LightManager
    {
    public:
        /* We use vectors to store lights
         * in order to use its consecutive memory storage
         * We also set a maximum number of each lights
         * So no problem of reallocation; we'll reserve enough space at init.
         */
    private:
        ListPLight _listPoint;
        ListDLight _listDirection;
        AmbiantLight _ambiant;

    public:
        LightManager();

        void addPoint(const PointLight& pLight);
        void addDir(const DirectionLight& dLight);
        void setAmbiant(const AmbiantLight& ambiant);
        void removePoint(const SizeInt index);
        void removeDir(const SizeInt index);


        void removeLastPoint() {this->removePoint(_listPoint.size()-1);}
        void removeLastDir() {this->removeDir(_listDirection.size()-1);}


        inline const AmbiantLight& ambiant() const {return _ambiant;}
        inline const ListPLight& listPoint() const {return _listPoint;}
        inline const ListDLight& listDirection() const {return _listDirection;}

    private:
        void CBaddPoint(const PointLight& pLight);
        void CBaddDir(const DirectionLight& dLight);
        void CBsetAmbiant(const AmbiantLight& ambiant);
        void CBremovePoint(const SizeInt index);
        void CBremoveDir(const SizeInt index);


    };


    typedef std::unique_ptr<LightManager> LightManagerPtr;
}

#endif //WORLD_IMAKER_LIGHT_HPP
