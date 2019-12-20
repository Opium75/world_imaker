//
// Created by piptouque on 19/12/2019.
//

#ifndef WORLD_IMAKER_PATTERNMANAGER_HPP
#define WORLD_IMAKER_PATTERNMANAGER_HPP

#pragma once

#include <vector>

#include <glimac/Cube.hpp>

namespace wim
{
    static const std::size_t NB_PATTERNS_CUBE = 2;
    static const double DEFAULT_CUBE_SIZE = 1;

    class PatternManager
    {
    public:
        typedef std::vector<glimac::AbstractCube> ListPattern;
    private:
        ListPattern _listPattern;
    public:
        PatternManager() : _listPattern(NB_PATTERNS_CUBE)
        {
            loadPatterns();
        }
        ~PatternManager() = default;


        void loadPatterns()
        {
            _listPattern.at(0) = glimac::TexturedCube(DEFAULT_CUBE_SIZE);
            _listPattern.at(1) = glimac::ColouredCube(DEFAULT_CUBE_SIZE);
        }
    };


}
#endif //WORLD_IMAKER_PATTERNMANAGER_HPP
