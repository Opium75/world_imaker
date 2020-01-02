//
// Created by piptouque on 28/12/2019.
//

#include "../include/wim/Displayable.hpp"

namespace wim
{
    ListITOPtr Displayable::_textures(nullptr);

    const ITO& Displayable::ito() const
    {
        if( _textureIndex >= _textures->size())
            throw Exception(ExceptCode::OUT_OF_RANGE,1,"Invalid index for ITO.");
        return _textures->at(_textureIndex);
    }


    SizeInt Displayable::getNumberTextures()
    {
        return _textures->size();
    }

    bool Displayable::isTextured() const
    {
        return this->getDisplayPattern() == DisplayPattern::TEXTURED_CUBE;
    }

    bool Displayable::isWireframe() const
    {
        return this->getDisplayPattern() == DisplayPattern::WIREFRAME_CUBE;
    }

    bool Displayable::isInForeground() const
    {
            //Only the cursor will be in the foreground
            //so same as wireframe
            return this->isWireframe();
    }

    void Displayable::linkTextures(const ListITOPtr& textures)
    {
        _textures = textures;
    }

    const Material& Renderable::getMaterial() const {return _objectPtr->getMaterial();}
    DisplayPattern Renderable::getDisplayPattern() const {return _objectPtr->getDisplayPattern();}
    const Anchor& Renderable::getAnchor() const {return _anchor;}
    const ITO& Renderable::ito() const {return _objectPtr->ito();}

    bool Renderable::isTextured()  const {return  _objectPtr->isTextured();}
    bool Renderable::isWireframe()  const {return  _objectPtr->isWireframe();}
    bool Renderable::isInForeground()  const {return  _objectPtr->isInForeground();}

}