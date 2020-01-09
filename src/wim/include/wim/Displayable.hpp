//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_DISPLAYABLE_HPP
#define WORLD_IMAKER_DISPLAYABLE_HPP

#pragma once


#include "Types.hpp"
#include "Vec3D.hpp"
#include "CommonDisplay.hpp"

#include "Randomisable.hpp"


#include "ITO.hpp"
#include "Material.hpp"

namespace wim
{


    enum class DisplayPattern : SizeInt
    {
        COLOURED_CUBE,
        TEXTURED_CUBE,
        WIREFRAME_CUBE,
        TEXTURED_QUAD,
        HIDDEN_QUAD
    };

    ///An interface for elements which will be shown in the world window
    class Displayable
    {
    protected:
        Material _material;
    private:
        //Will cast the accumulator when needed instead of using an integer
        SizeInt _textureIndex;
    protected:
        static ListITOPtr _textures;
    protected:
        Displayable() = default;
        Displayable(const Material &material, const SizeInt textureIndex=0) : _material(material), _textureIndex(textureIndex) {}
    public:
        //Should be overridden by every class, with one of the above Patterns
        virtual DisplayPattern getDisplayPattern() const = 0;
        const Material& material() const {return _material;}
        Material& material() {return _material;}

        SizeInt textureIndex() const {return _textureIndex;};
        const ITO& ito() const;

        void setTextureIndex(const SizeInt index);
        void setNextTexture();

        static SizeInt getNumberTextures();

        bool isTextured() const;
        bool isInForeground() const;
        bool isHidden() const;

        static void linkTextures(const ListITOPtr& textures);

    };

    class Renderable
    {
    protected:
        const Displayable* const _objectPtr;
        Anchor _anchor;
        FloatType _rotX, _rotY;
    public:
        Renderable(const Displayable& object, const Anchor& anchor, const FloatType rotX=0, const FloatType rotY=0);
        ~Renderable();

        const Material& material() const;
        DisplayPattern getDisplayPattern() const;
        const Anchor& anchor() const;
        FloatType getRotX() const;
        FloatType getRotY() const;
        const ITO& ito() const;

        bool isTextured()  const;
        bool isInForeground()  const;
        bool isHidden() const;
    };


}

#endif //WORLD_IMAKER_DISPLAYABLE_HPP
