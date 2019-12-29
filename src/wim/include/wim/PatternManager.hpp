//
// Created by piptouque on 19/12/2019.
//

#ifndef WORLD_IMAKER_PATTERNMANAGER_HPP
#define WORLD_IMAKER_PATTERNMANAGER_HPP

#pragma once

#include <vector>

#include <glimac/Cube.hpp>

#include "Types.hpp"
#include "Exception.hpp"
#include "Displayable.hpp"
#include "BufferManager.hpp"

namespace wim
{
    static const SizeInt NB_PATTERNS_CUBE = 2;
    static const double DEFAULT_CUBE_SIZE = 1.;

    typedef std::unique_ptr<glimac::AbstractCube> PatternPtr;

    class PatternManager
    {
    public:
        typedef std::vector<PatternPtr> ListPatternPtr;
    private:
        ListPatternPtr _listPatternPtr;
    public:
        PatternManager() : _listPatternPtr(NB_PATTERNS_CUBE)
        {
            loadPatterns();
        }
        ~PatternManager() = default;


        void loadPatterns()
        {
            _listPatternPtr.at((SizeInt)DisplayPattern::COLOURED_CUBE) = std::make_unique<glimac::CubePattern>(DEFAULT_CUBE_SIZE);
            _listPatternPtr.at((SizeInt)DisplayPattern::TEXTURED_CUBE) = std::make_unique<glimac::CubePattern>(DEFAULT_CUBE_SIZE);
        }

        const PatternPtr& at(const DisplayPattern dispPat)
        {
            SizeInt index = (SizeInt)dispPat;
            if( index > _listPatternPtr.size() )
                throw Exception(ExceptCode::OUT_OF_RANGE, 1,
                        std::string("Pattern does not exist: ") + std::to_string(index) + '.' );
            return _listPatternPtr.at(index);
        }

        inline void draw(const Renderable& item) const
        {
            bool isTextured = item.isTextured();
            if( isTextured )
            {
                glBindTexture(GL_TEXTURE_CUBE_MAP, item.getTextureId());
            }
            _listPatternPtr.at((SizeInt)item.getDisplayPattern())->draw();
            if( isTextured )
                glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }

    };


}
#endif //WORLD_IMAKER_PATTERNMANAGER_HPP
