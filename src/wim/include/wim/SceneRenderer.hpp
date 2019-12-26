//
// Created by piptouque on 20/12/2019.
//

#ifndef WORLD_IMAKER_SCENERENDERER_HPP
#define WORLD_IMAKER_SCENERENDERER_HPP

#pragma once

#include <memory>
#include <stack>
#include <deque>

#include "Displayable.hpp"
#include "Listener.hpp"

#include "PatternManager.hpp"
#include "ShaderManager.hpp"
#include "Model.hpp"

namespace wim
{
    /*This class should be given the objects to be displayed
     * At every display iteration.
     * It can then optimise calls to shaders.
     */
    /* It is subscibed to Light Manager
     * so that is can send lights to shaders
     * only when there is a change
     */
    class SceneRenderer : protected Listener
    {
    public:
        typedef std::stack<Renderable> RenderingStack;
    private:
        ModelPtr _model;
        ShaderManager _shaders;
        PatternManager _patterns;
        RenderingStack _stack;
    public:
        SceneRenderer(const char* appPath, const ModelPtr& model);
        ~SceneRenderer();

        inline void addToStack(const Renderable& item) {_stack.push(item);}

        inline const LightManagerPtr& lightManager() const {return _model->lightManager();}
        inline const CameraManagerPtr& cameraManager() const {return _model->cameraManager();}

        inline UniformMatrix getCameraViewMatrix() const {return this->cameraManager()->getCameraViewMatrix();}
        inline UniformMatrix getElementModelViewMatrix(const Renderable& item){return this->cameraManager()->getElementModelViewMatrix(item);}
        inline UniformMatrix getProjectionMatrix() const{return this->cameraManager()->getProjectionMatrix();}


        inline void updateMaterial(const Material& material){return _shaders.updateMaterial(material);}
        inline void updateMVPNMatrices(const UniformMatrix& MVMatrix, const UniformMatrix& ProjMatrix){return _shaders.updateMVPNMatrices(MVMatrix, ProjMatrix);}

        void updateLights() const;

        void update() override
        {
            this->updateLights();
        }

        inline void drawPattern(const DisplayPattern dispPat){_patterns.draw(dispPat);}
        //todo: this.
        ///brief: render Displayable elements in stack, with respect to active Camera, lighting, and Shaders
        void render();
    };

}

#endif //WORLD_IMAKER_SCENERENDERER_HPP
