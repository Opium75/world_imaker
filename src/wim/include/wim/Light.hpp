//
// Created by piptouque on 18/12/2019.
//

#ifndef WORLD_IMAKER_LIGHT_HPP
#define WORLD_IMAKER_LIGHT_HPP

#include <deque>

#include "Types.hpp"
#include "Vec3D.hpp"

#pragma once

namespace wim {

    class AbstractLight {
    private:
        FloatType _intensity;

    public:
        AbstractLight(const FloatType intensity) : _intensity(intensity) {}
        virtual ~AbstractLight() = 0;
    };

    class PointLight : public AbstractLight {

    private:
        Point3Int _origin; //coordinates of the light in World.
    public:
        PointLight(const FloatType intensity, const Point3Int& origin) : AbstractLight(intensity), _origin(origin) {}
        ~PointLight() override = default;
    };

    class DirectionalLight : public AbstractLight {

    private:
        Vec3D _direction;
    public:
        DirectionalLight(const FloatType intensity, const Vec3D& direction) : AbstractLight(intensity), _direction(direction) {}
        ~DirectionalLight() override = default;
    };

    class LightManager
    {
    public:
        typedef std::deque<PointLight> ListPLight;
        typedef std::deque<DirectionalLight> ListDLight;
    private:
        ListPLight _listPoint;
        ListDLight _listDir;
    public:
        LightManager() = default;
        ~LightManager() = default;
        void addPoint(const PointLight& pLight) {_listPoint.push_back(pLight);}
        void addDir(const DirectionalLight& dLight) {_listDir.push_back(dLight);}

        void removePoint(const size_t index) {_listPoint.erase(_listPoint.begin()+index);}
        void removeDir(const size_t index) {_listDir.erase(_listDir.begin()+index);}


    };


    //Light Manager needs to be shared between Model and Scene Renderer
    typedef std::shared_ptr<LightManager> LightManagerPtr;
}

#endif //WORLD_IMAKER_LIGHT_HPP
