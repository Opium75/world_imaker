//
// Created by piptouque on 19/12/2019.
//

#ifndef WORLD_IMAKER_PATTERNMANAGER_HPP
#define WORLD_IMAKER_PATTERNMANAGER_HPP

#pragma once

#include <vector>
#include <memory>

#include <glimac/Pattern.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Quad.hpp>

#include "Types.hpp"
#include "Exception.hpp"
#include "Displayable.hpp"

#include "Quad.hpp"
#include "FBO.hpp"

namespace wim
{


    typedef std::shared_ptr<glimac::Pattern> PatternPtr;

    class PatternManager
    {
    public:
        typedef std::vector<PatternPtr> ListPatternPtr;
    private:
        ListPatternPtr _listPatternPtr;
    public:
        PatternManager();
        ~PatternManager() = default;


        void draw(const Renderable& item) const;
        void drawFramebuffer(const FBO& framebuffer) const;
    private:
        void loadPatterns();

        void drawRenderable(const Renderable& item) const;
        void drawColoured(const Renderable& item) const;
        void drawTextured(const Renderable& item) const;
        void drawWireframe(const Renderable& item) const;
        void drawHidden(const Renderable& item) const;

        const PatternPtr& at(const DisplayPattern& dispPat) const;
        PatternPtr& at(const DisplayPattern& dispPat);
    };

    typedef std::unique_ptr<PatternManager> PatternManagerPtr;
}
#endif //WORLD_IMAKER_PATTERNMANAGER_HPP
