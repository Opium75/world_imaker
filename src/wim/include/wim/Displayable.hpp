//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYABLE_HPP
#define WORLD_IMAKER_DISPLAYABLE_HPP

#pragma once

#include "Types.hpp"
#include "Vec3D.hpp"
#include "Material.hpp"

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
        Displayable(const Material &material, const SizeInt textureIndex=0) : _material(material), _textureIndex(textureIndex) {}
    public:
        //Should be overridden by every class, with one of the above Patterns
        virtual DisplayPattern getDisplayPattern() const = 0;
        const Material& getMaterial() const {return _material;}
        GLint getTextureId() const
        {
            if( _textureIndex >= _textures->size())
                throw Exception(ExceptCode::OUT_OF_RANGE,1,"Invalid index for ITO.");
            return _textures->at(_textureIndex)._ito;
        }

        inline static SizeInt getNumberTextures()
        {
            return _textures->size();
        }

        inline bool isTextured() const
        {return this->getDisplayPattern() == DisplayPattern::TEXTURED_CUBE;}

        static void linkTextures(ListITOPtr& textures)
        {_textures = textures;}
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

        inline bool isTextured()  const
        {
           return  _objectPtr->isTextured();
        }
    };


}

#endif //WORLD_IMAKER_DISPLAYABLE_HPP
