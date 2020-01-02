//
// Created by piptouque on 29/12/2019.
//

#include "wim/PatternManager.hpp"

namespace wim
{
    PatternManager::PatternManager() : _listPatternPtr(NB_PATTERNS)
    {
        loadPatterns();
    }

    void PatternManager::loadPatterns()
    {
        glm::vec2 squadCentre(DEFAULT_FRAMEBUFFER_SQUAD_CENTRE_X, DEFAULT_FRAMEBUFFER_SQUAD_CENTRE_Y);
        PatternPtr cubePattern = std::make_shared<glimac::CubePattern>(DEFAULT_CUBE_SIZE);
        PatternPtr quadPattern = std::make_shared<glimac::QuadPattern>(squadCentre, DEFAULT_FRAMEBUFFER_SQUAD_SIZE);
        //same pattern for everyone
        this->at(DisplayPattern::COLOURED_CUBE) = cubePattern;
        this->at(DisplayPattern::TEXTURED_CUBE) = cubePattern;
        this->at(DisplayPattern::WIREFRAME_CUBE) = cubePattern;
        this->at(DisplayPattern::QUAD) = quadPattern;
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
        this->at(item.getDisplayPattern())->draw();
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

    void PatternManager::drawFramebuffer(const FBO& framebuffer) const
    {
        glBindTexture(GL_TEXTURE_2D, framebuffer.viewportTexture().id());
            this->at(DisplayPattern::QUAD)->draw();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void PatternManager::drawColoured(const Renderable& item) const
    {
        this->drawRenderable(item);
    }

    void PatternManager::drawTextured(const Renderable& item) const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, item.ito().id());
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