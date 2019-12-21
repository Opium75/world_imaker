//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYABLE_HPP
#define WORLD_IMAKER_DISPLAYABLE_HPP

#pragma once

#include "Types.hpp"
#include "Vec3D.hpp"

namespace wim
{
    enum class DisplayPattern
    {
        FULL_CUBE,
        WIREFRAME_CUBE
    };

    ///An interface for elements which will be shown in the world window
    class Displayable
    {
    protected:
        //Should be overridden by every class, with one of the above Patterns
        virtual DisplayPattern getDisplayPattern() const = 0;
    };

    class Renderable
    {
    public:
        typedef Point3Int Anchor;
    protected:
        const Displayable* const _objectPtr;
        Anchor _anchor;
    public:
        Renderable(const Displayable& object, const Anchor& anchor) : _objectPtr(&object), _anchor(anchor)
        {

        }

        ~Renderable()
        {
            //We do NOT delete the displayable object
        }

    };



}

#endif //WORLD_IMAKER_DISPLAYABLE_HPP
