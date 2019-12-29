//
// Created by piptouque on 29/12/2019.
//

#include "wim/PatternManager.hpp"

namespace wim
{

    void PatternManager::loadPatterns()
    {
        PatternPtr pattern =std::make_shared<glimac::CubePattern>(DEFAULT_CUBE_SIZE);
        //same pattern for everyone
        this->at(DisplayPattern::COLOURED_CUBE) = pattern;
       this->at(DisplayPattern::TEXTURED_CUBE) = pattern;
        this->at(DisplayPattern::WIREFRAME_CUBE) = pattern;
    }

    const PatternPtr& PatternManager::at(const DisplayPattern& dispPat) const
    {
        SizeInt index = (SizeInt)dispPat;
        if( index > _listPatternPtr.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1,
                            std::string("Pattern does not exist: ") + std::to_string(index) + '.' );
        return _listPatternPtr.at(index);
    }

    PatternPtr& PatternManager::at(const DisplayPattern& dispPat)
    {
        SizeInt index = (SizeInt)dispPat;
        if( index > _listPatternPtr.size() )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1,
                            std::string("Pattern does not exist: ") + std::to_string(index) + '.' );
        return _listPatternPtr.at(index);
    }

    void PatternManager::drawRenderable(const Renderable& item) const
    {
        _listPatternPtr.at((SizeInt)item.getDisplayPattern())->draw();
    }

    void PatternManager::draw(const Renderable& item) const
    {
        if( item.isTextured() )
            this->drawTextured(item);
        else if ( item.isWireframe() )
            this->drawWireframe(item);
        else
            this->drawColoured(item);
    }

    void PatternManager::drawColoured(const Renderable& item) const
    {
        this->drawRenderable(item);
    }

    void PatternManager::drawTextured(const Renderable& item) const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, item.getTextureId());
            this->drawRenderable(item);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void PatternManager::drawWireframe(const Renderable& item) const
    {
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
            this->drawRenderable(item);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }

}