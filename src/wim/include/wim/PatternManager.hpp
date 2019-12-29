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
    static const SizeInt NB_PATTERNS_CUBE = 3;
    static const double DEFAULT_CUBE_SIZE = 1.;

    typedef std::shared_ptr<glimac::AbstractCube> PatternPtr;

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


        void draw(const Renderable& item) const;
    private:
        void loadPatterns();

        void drawRenderable(const Renderable& item) const;
        void drawColoured(const Renderable& item) const;
        void drawTextured(const Renderable& item) const;
        void drawWireframe(const Renderable& item) const;

        const PatternPtr& at(const DisplayPattern& dispPat) const;
        PatternPtr& at(const DisplayPattern& dispPat);


    };


}
#endif //WORLD_IMAKER_PATTERNMANAGER_HPP
