//
// Created by piptouque on 28/12/2019.
//

#include "../include/wim/Displayable.hpp"

namespace wim
{
    ListITOPtr Displayable::_textures(nullptr);

    GLint Displayable::getTextureId() const
    {
        if( _textureIndex >= _textures->size())
            throw Exception(ExceptCode::OUT_OF_RANGE,1,"Invalid index for ITO.");
        return _textures->at(_textureIndex)._ito;
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

    void Displayable::linkTextures(ListITOPtr& textures)
    {
        _textures = textures;
    }


}