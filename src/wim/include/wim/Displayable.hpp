//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYABLE_HPP
#define WORLD_IMAKER_DISPLAYABLE_HPP

#pragma once

#include "Types.hpp"
#include "Vec3D.hpp"

#include "BufferManager.hpp"

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
        SizeInt _textureIndex;
        static ListITOPtr _textures;
    protected:
        Displayable() = default;
        Displayable(const Material &material, const SizeInt textureIndex=0) : _material(material), _textureIndex(textureIndex) {}
    public:
        //Should be overridden by every class, with one of the above Patterns
        virtual DisplayPattern getDisplayPattern() const = 0;
        const Material& getMaterial() const {return _material;}
        GLint getTextureId() const;

        static SizeInt getNumberTextures();

        bool isTextured() const;
        bool isWireframe() const;
        bool isInForeground() const;

        static void linkTextures(ListITOPtr& textures);
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
        const Material& getMaterial() const {return _objectPtr->getMaterial();}
        DisplayPattern getDisplayPattern() const {return _objectPtr->getDisplayPattern();}
        const Anchor& getAnchor() const {return _anchor;}
        GLint getTextureId() const {return _objectPtr->getTextureId(); }

        inline bool isTextured()  const {return  _objectPtr->isTextured();}
        inline bool isWireframe()  const {return  _objectPtr->isWireframe();}
        inline bool isInForeground()  const {return  _objectPtr->isInForeground();}
    };


}

#endif //WORLD_IMAKER_DISPLAYABLE_HPP
