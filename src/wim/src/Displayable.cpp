//
// Created by piptouque on 28/12/2019.
//

#include "../include/wim/Displayable.hpp"

namespace wim
{
    ListITOPtr Displayable::_textures(nullptr);

    Renderable::Renderable(const Displayable& object, const Anchor& anchor, const FloatType rotX, const FloatType rotY) :
        _objectPtr(&object), _anchor(anchor), _rotX(rotX), _rotY(rotY)
    {

    }

    Renderable::~Renderable()
    {
        //We do NOT delete the displayable object
    }


    void Displayable::setTextureIndex(const SizeInt textureIndex)
    {
        if( textureIndex >= getNumberTextures())
        {
            throw Exception(ExceptCode::OUT_OF_RANGE,1,"Invalid index for texture.");
        }
        _textureIndex = textureIndex;
    }


    void Displayable::setNextTexture()
    {
        _textureIndex = (_textureIndex+1)%getNumberTextures();
    };

    FloatType Renderable::getRotX() const
    {
        return _rotX;
    }


    FloatType Renderable::getRotY() const
    {
        return _rotY;
    }

    const ITO& Displayable::ito() const
    {
        if( textureIndex() >= getNumberTextures())
        {
            throw Exception(ExceptCode::OUT_OF_RANGE,1,"Invalid index for ITO.");
        }
        return _textures->at(textureIndex());
    }


    SizeInt Displayable::getNumberTextures()
    {
        return _textures->size();
    }

    bool Displayable::isTextured() const
    {
        return this->getDisplayPattern() == DisplayPattern::TEXTURED_CUBE;
    }


    bool Displayable::isInForeground() const
    {
            //Only the cursor will be in the foreground
            //so same as wireframe
            return this->getDisplayPattern() == DisplayPattern::WIREFRAME_CUBE;
    }

    bool Displayable::isHidden() const
    {
        //The squads at the base of the DisplayableStacks will not be visible.
        return this->getDisplayPattern() == DisplayPattern::HIDDEN_QUAD;
    }

    void Displayable::linkTextures(const ListITOPtr& textures)
    {
        _textures = textures;
    }

    const Material& Renderable::material() const {return _objectPtr->material();}
    DisplayPattern Renderable::getDisplayPattern() const {return _objectPtr->getDisplayPattern();}
    const Anchor& Renderable::anchor() const {return _anchor;}
    const ITO& Renderable::ito() const {return _objectPtr->ito();}

    bool Renderable::isTextured()  const {return  _objectPtr->isTextured();}
    bool Renderable::isInForeground()  const {return  _objectPtr->isInForeground();}
    bool Renderable::isHidden()  const {return  _objectPtr->isHidden();}


}