//
// Created by piptouque on 02/01/2020.
//

#ifndef WORLD_IMAKER_QUAD_HPP
#define WORLD_IMAKER_QUAD_HPP

#pragma once

#include "Displayable.hpp"

namespace wim
{

    static constexpr const GLfloat DEFAULT_BASE_QUAD_OFFSET_Y = -0.5f;
    static constexpr const GLfloat DEFAULT_BASE_QUAD_ANGLE_X = 90.f; //in degrees

    class Quad : public Displayable
    {
    public:
        Quad() = default;
        Renderable getRenderable(const XUint x, const ZUint z) const;
        virtual DisplayPattern getDisplayPattern() const = 0;
    };

    ///brief: a class of invisible objects which will be selectable at the base of the CubeStacks.
    class HiddenBaseQuad : public Quad
    {
    public:
        HiddenBaseQuad() = default;
        DisplayPattern getDisplayPattern() const override;
    };

    class BaseQuad : public  Quad
    {
    public:
        BaseQuad() = default;
        DisplayPattern getDisplayPattern() const override;
    };

}

#endif //WORLD_IMAKER_QUAD_HPP
