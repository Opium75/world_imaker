//
// Created by piptouque on 21/12/2019.
//

#ifndef WORLD_IMAKER_MODEL_HPP
#define WORLD_IMAKER_MODEL_HPP

#pragma once

#include <memory>

#include "Types.hpp"
#include "CubeWorld.hpp"
#include "Light.hpp"
#include "CameraManager.hpp"
#include "Cursor.hpp"
#include "ProceduralGenerator.hpp"

namespace wim {

    static constexpr XUint DEFAULT_CUBEWORLD_WIDTH = 3;
    static constexpr YUint DEFAULT_CUBEWORLD_LENGTH = 3;
    static constexpr ZUint DEFAULT_CUBEWORLD_HEIGHT = 3;


    //A structure for everything which needs computation
    class Model {
    public:
    private:
        WorldPtr _world;
        LightManagerPtr _lights;
        CameraManagerPtr _cameras;
        CursorPtr _cursor;

    public:
        Model() :
                _world(std::make_shared<CubeWorld>()),
                _lights(std::make_unique<LightManager>()),
                _cameras(std::make_unique<CameraManager>()),
                _cursor(std::make_unique<Cursor>(_world))
        {

        }
        ~Model() = default;

        inline const WorldPtr& world() const {return _world;}
        inline WorldPtr& world() {return _world;}

        inline const LightManagerPtr& lightManager() const {return _lights;}
        inline LightManagerPtr& lightManager() {return _lights;}

        inline const CameraManagerPtr& cameraManager() const {return _cameras;}
        inline CameraManagerPtr& cameraManager() {return _cameras;}

        inline const CursorPtr& cursor() const {return _cursor;}
        inline CursorPtr& cursor() {return _cursor;}

        inline const Point3Uint& getCursorPosition() const {return _cursor->getPosition();}

        void addPointLight(const PointLight& pLight) {this->_lights->addPoint(pLight);}
        void addDirectionLight(const DirectionLight& dLight) {this->_lights->addDir(dLight);}


        void removePointLight(const SizeInt index) {this->_lights->removePoint(index);}
        void removeDirectionLight(const SizeInt index) {this->_lights->removeDir(index);}
    };

    //Model will be shared between Controllers, Scene Renderer and Interface
    typedef std::shared_ptr<Model> ModelPtr;
}
#endif //WORLD_IMAKER_MODEL_HPP
