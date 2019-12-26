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

    static const XUint DEFAULT_CUBEWORLD_WIDTH = 3;
    static const YUint DEFAULT_CUBEWORLD_LENGTH = 3;
    static const ZUint DEFAULT_CUBEWORLD_HEIGHT = 3;


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
        Model(const XUint worldWidth = DEFAULT_CUBEWORLD_WIDTH,
              const YUint worldLength = DEFAULT_CUBEWORLD_LENGTH,
              const ZUint worldHeight = DEFAULT_CUBEWORLD_HEIGHT) :
            _world(std::make_unique<CubeWorld>(CubeWorld::Random(worldWidth, worldLength, worldHeight))),
            _lights(std::make_unique<LightManager>()),
            _cameras(std::make_unique<CameraManager>())
             {}
        ~Model() = default;

        inline const WorldPtr& world() const {return _world;}
        inline WorldPtr& world() {return _world;}
        inline const LightManagerPtr& lightManager() const {return _lights;}
        inline LightManagerPtr& lightManager() {return _lights;}
        inline const CameraManagerPtr& cameraManager() const {return _cameras;}
        inline CameraManagerPtr& cameraManager() {return _cameras;}


        void addPointLight(const PointLight& pLight) {this->_lights->addPoint(pLight);}
        void addDirectionalLight(const DirectionalLight& dLight) {this->_lights->addDir(dLight);}
    };

    //Model will be shared between Controllers, Scene Renderer and Interface
    typedef std::shared_ptr<Model> ModelPtr;
}
#endif //WORLD_IMAKER_MODEL_HPP
