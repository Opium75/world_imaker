//
// Created by piptouque on 20/12/2019.
//

#ifndef WORLD_IMAKER_SCENERENDERER_HPP
#define WORLD_IMAKER_SCENERENDERER_HPP

#pragma once

#include <stack>
#include <deque>

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
        RenderingStack _stack;
    public:
        SceneRenderer(const char* appPath, const LightManagerPtr& lights) : _shaders(appPath), _patterns(), _lights(lights), _stack()
        {

        }

        inline void addToStack(const Renderable& item) {_stack.push(item);}



    };

}

#endif //WORLD_IMAKER_SCENERENDERER_HPP
