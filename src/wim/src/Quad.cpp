//
// Created by piptouque on 02/01/2020.
//

#include "../include/wim/Quad.hpp"

namespace wim
{


    DisplayPattern BaseQuad::getDisplayPattern() const
    {
        return DisplayPattern::HIDDEN_QUAD;
    }



    Renderable BaseQuad::getRenderable(const XUint x, const ZUint z) const
    {
        return Renderable(*this,
                          Anchor(x,
                                 DEFAULT_BASE_QUAD_OFFSET_Y,
                                 z),
                          DEFAULT_BASE_QUAD_ANGLE_X,
                          0
        );
    }
}