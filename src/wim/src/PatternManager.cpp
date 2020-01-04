//
// Created by piptouque on 29/12/2019.
//

#include "../include/wim/PatternManager.hpp"



namespace wim
{

    static constexpr const SizeInt NB_PATTERNS = 5;
    static constexpr const GLfloat DEFAULT_CUBE_SIZE = 1.f;


    static constexpr const GLfloat DEFAULT_FRAMEBUFFER_QUAD_SIZE = 2.f;
    static constexpr const GLfloat DEFAULT_FRAMEBUFFER_QUAD_CENTRE_X = -1.f;
    static constexpr const GLfloat DEFAULT_FRAMEBUFFER_QUAD_CENTRE_Y = -1.f;


    static constexpr const GLfloat DEFAULT_BASE_QUAD_SIZE = 1.f;
    static constexpr const GLfloat DEFAULT_BASE_QUAD_CENTRE_X = -0.5f;
    static constexpr const GLfloat DEFAULT_BASE_QUAD_CENTRE_Y = -0.5f;

    PatternManager::PatternManager() : _listPatternPtr(NB_PATTERNS)
    {
        loadPatterns();
    }

    void PatternManager::loadPatterns()
    {
        glm::vec2 framebufferQuadCentre(DEFAULT_FRAMEBUFFER_QUAD_CENTRE_X, DEFAULT_FRAMEBUFFER_QUAD_CENTRE_Y);
        glm::vec2 baseQuadCentre(DEFAULT_BASE_QUAD_CENTRE_X, DEFAULT_BASE_QUAD_CENTRE_Y);
        PatternPtr cubePattern = std::make_shared<glimac::CubePattern>(DEFAULT_CUBE_SIZE);
        PatternPtr framebufferQuadPattern = std::make_shared<glimac::QuadPattern>(framebufferQuadCentre, DEFAULT_FRAMEBUFFER_QUAD_SIZE);
        PatternPtr baseQuadPattern = std::make_shared<glimac::QuadPattern>(baseQuadCentre, DEFAULT_BASE_QUAD_SIZE);
        //same pattern for everyone
        this->at(DisplayPattern::COLOURED_CUBE) = cubePattern;
        this->at(DisplayPattern::TEXTURED_CUBE) = cubePattern;
        this->at(DisplayPattern::WIREFRAME_CUBE) = cubePattern;
        this->at(DisplayPattern::TEXTURED_QUAD) = framebufferQuadPattern;
        this->at(DisplayPattern::HIDDEN_QUAD) = baseQuadPattern;
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
        switch(item.getDisplayPattern())
        {
            case DisplayPattern::COLOURED_CUBE :
                this->drawColoured(item);
                break;
            case DisplayPattern::TEXTURED_CUBE:
                this->drawTextured(item);
                break;
            case DisplayPattern::WIREFRAME_CUBE :
                this->drawWireframe(item);
                break;
            case DisplayPattern::TEXTURED_QUAD :
                //drawn with drawFramebuffer
                break;
            case DisplayPattern::HIDDEN_QUAD :
                this->drawHidden(item);
                break;
            default:
                break;
        }
    }

    void PatternManager::drawFramebuffer(const FBO& framebuffer) const
    {
        glBindTexture(GL_TEXTURE_2D, framebuffer.viewportTexture().id());
            this->at(DisplayPattern::TEXTURED_QUAD)->draw();
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

    void PatternManager::drawHidden(const Renderable& item) const
    {
        //Nothing more to do, the shader we use does all the work.
        this->drawRenderable(item);
    }

}