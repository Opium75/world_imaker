//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYABLE_HPP
#define WORLD_IMAKER_DISPLAYABLE_HPP

#pragma once

#include "Types.hpp"
#include "Vec3D.hpp"
#include "Material.hpp"

namespace wim
{
    enum class DisplayPattern : SizeInt
    {
        COLOURED_CUBE,
        TEXTURED_CUBE,
        WIREFRAME_CUBE
    };

    ///An interface for elements which will be shown in the world window
    class Displayable
    {
    protected:
        Material _material;
    protected:
        Displayable(const Material &material) : _material(material) {}
    public:
        //Should be overridden by every class, with one of the above Patterns
        virtual DisplayPattern getDisplayPattern() const = 0;
        const Material& getMaterial() const {return this->_material;}
    };

    class Renderable
    {
    public:
        typedef Point3D Anchor;
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
        const Material& getMaterial() const {return this->_objectPtr->getMaterial();}
        DisplayPattern getDisplayPattern() const {return _objectPtr->getDisplayPattern();}
        const Anchor& getAnchor() const {return _anchor;}
    };



}

#endif //WORLD_IMAKER_DISPLAYABLE_HPP
