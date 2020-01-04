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

    ///brief: a class of invisible objects which will be selectable at the base of the CubeStacks.
    class BaseQuad : public Displayable
    {
    public:
        BaseQuad() = default;
        DisplayPattern getDisplayPattern() const override;
        Renderable getRenderable(const XUint x, const ZUint z) const;
    };
}

#endif //WORLD_IMAKER_QUAD_HPP
