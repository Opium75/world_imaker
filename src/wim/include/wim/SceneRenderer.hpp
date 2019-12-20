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
        typedef std::deque<AbstractLight> ListLight;
        typedef std::stack<Displayable> RenderingStack;
    private:
        ShaderManager _shaders;
        PatternManager _patterns;
        RenderingStack _stack;
    public:
        SceneRenderer(const char* appPath) : _shaders(appPath), _patterns()
        {

        }


    };

}

#endif //WORLD_IMAKER_SCENERENDERER_HPP
