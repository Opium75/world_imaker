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
#include "PatternManager.hpp"
#include "ShaderManager.hpp"
#include "Model.hpp"

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
        ModelPtr _model;
        ShaderManager _shaders;
        PatternManager _patterns;
        RenderingStack _stack;
    public:
        SceneRenderer(const char* appPath, const ModelPtr& model):
        _model(model),
        _shaders(appPath), _patterns(),_stack()
        {
        }

        inline void addToStack(const Renderable& item) {_stack.push(item);}

        inline const LightManagerPtr& getLightManagerPtr() const {return _model->getLightManagerPtr();}
        inline const CameraManagerPtr& getCameraManagerPtr() const {return _model->getCameraManagerPtr();}

        inline UniformMatrix getCameraViewMatrix() const {
            return this->getCameraManagerPtr()->getCameraViewMatrix();
        }
        inline UniformMatrix getElementModelViewMatrix(const Renderable& item)
        {
            return this->getCameraManagerPtr()->getElementModelViewMatrix(item);
        }
        inline UniformMatrix getProjectionMatrix() const
        {
            return this->getCameraManagerPtr()->getProjectionMatrix();
        }


        inline void updateMaterialCurrent(const Material& material)
        {
            return _shaders.updateMaterialCurrent(material);
        }
        inline void updateMVPNMatricesCurrent(const UniformMatrix& MVMatrix, const UniformMatrix& ProjMatrix)
        {
            return _shaders.updateMVPNMatricesCurrent(MVMatrix, ProjMatrix);
        }

        void updateLightsCurrent() const;

        inline void drawPattern(const DisplayPattern dispPat)
        {
           _patterns.draw(dispPat);
        }
        //todo: this.
        ///brief: render Displayable elements in stack, with respect to active Camera, lighting, and Shaders
        void render();
    };

}

#endif //WORLD_IMAKER_SCENERENDERER_HPP
