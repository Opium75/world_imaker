//
// Created by piptouque on 20/12/2019.
//

#ifndef WORLD_IMAKER_SCENERENDERER_HPP
#define WORLD_IMAKER_SCENERENDERER_HPP

#pragma once

#include <memory>
#include <stack>
#include <deque>

#include "CameraManager.hpp"
#include "Light.hpp"
#include "Displayable.hpp"
#include "PatternManager.hpp"
#include "ShaderManager.hpp"

namespace wim
{
    /*todo: This class should be given the objects to be displayed
     * At every display iteration.
     * It can then optimise calls to shaders.
     */
    class SceneRenderer
    {
    public:
        typedef std::stack<Renderable> RenderingStack;
    private:
        ShaderManager _shaders;
        PatternManager _patterns;
        LightManagerPtr _lights;
        CameraManagerPtr _cameras;
        RenderingStack _stack;
    public:
        SceneRenderer(const char* appPath):
        _shaders(appPath), _patterns(),
        _lights(std::make_unique<LightManager>()),
        _cameras(std::make_unique<CameraManager>()),
        _stack()
        {

        }

        inline void addToStack(const Renderable& item) {_stack.push(item);}

        inline UniformMatrix getActiveCameraViewMatrix() const {return _cameras->getActiveCameraViewMatrix();}

        inline const LightManagerPtr& getLightManagerPtr() const {return this->_lights;}
        inline const CameraManagerPtr& getCameraManagerPtr() const {return this->_cameras;}

        //todo: this.
        ///brief: render Displayable elements in stack, with respect to active Camera, lighting, and Shaders
        void render();
    };

}

#endif //WORLD_IMAKER_SCENERENDERER_HPP
