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

namespace wim {

    //A structure for everything which needs computation
    class Model {
    public:
        typedef std::unique_ptr<CubeWorld> WorldPtr;

    private:
        WorldPtr _world;
        LightManagerPtr _lights;
    public:
        Model() = default;
        Model(const XUint worldWidth, const YUint worldLength) :
            _world(std::make_unique<CubeWorld>(worldWidth, worldLength)), _lights(std::make_shared<LightManager>()) {}
        ~Model() = default;

        inline const WorldPtr& getWorldPtr() const {return _world;}
        inline const LightManagerPtr& getLightManagerPtr() const {return _lights;}


    };
}
#endif //WORLD_IMAKER_MODEL_HPP