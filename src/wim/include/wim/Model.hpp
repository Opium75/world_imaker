//
// Created by piptouque on 21/12/2019.
//

#ifndef WORLD_IMAKER_MODEL_HPP
#define WORLD_IMAKER_MODEL_HP

#pragma once

#include <memory>

#include "Types.hpp"
#include "CubeWorld.hpp"
#include "Light.hpp"
#include "CameraManager.hpp"

namespace wim {

    //A structure for everything which needs computation
    class Model {
    public:
        typedef std::unique_ptr<CubeWorld> WorldPtr;
    private:
        WorldPtr _world;
        LightManagerPtr _lights;
        CameraManagerPtr _cameras;
    public:
        Model() = default;
        Model(const XUint worldWidth, const YUint worldLength, const LightManagerPtr& lights, const CameraManagerPtr& cameras) :
            _world(std::make_unique<CubeWorld>(CubeWorld::Random(worldWidth, worldLength, (worldWidth+worldLength)/2))),
            _lights(lights) ,_cameras(cameras)
             {}
        ~Model() = default;

        inline const WorldPtr& getWorldPtr() const {return _world;}
        inline const LightManagerPtr& getLightManagerPtr() const {return _lights;}
        inline const CameraManagerPtr& getCameraManagerPtr() const {return _cameras;}


    };
}
#endif //WORLD_IMAKER_MODEL_HPP
