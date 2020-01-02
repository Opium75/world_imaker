//
// Created by piptouque on 29/12/2019.
//

#ifndef WORLD_IMAKER_CURSOR_HPP
#define WORLD_IMAKER_CURSOR_HPP

#pragma once

#include <memory>

#include "Types.hpp"
#include "Vec3D.hpp"
#include "CubeWorld.hpp"
#include "Selectable.hpp"

namespace wim
{
    class Cursor : public Displayable
    {
    private:
        Anchor _position;
        WorldPtr _world;
        SelectablePtr _selected;
    public:
        Cursor(const WorldPtr& world) : Displayable(), _world(world) {}
        ~Cursor() = default;


        void moveX(const XInt delta);
        void moveY(const YInt delta);
        void moveZ(const ZInt delta);

        void setPosition(const XUint x, const YUint y, const ZUint z);
        void setPosition(const Point3Uint& position);
        const Anchor& getPosition() const;

        inline XUint getWorldWidth() const {return _world->getWidth();}
        inline YUint getWorldLength() const {return _world->getLength();}

        DisplayPattern getDisplayPattern() const override
        {
            return DisplayPattern::WIREFRAME_CUBE;
        }
    private:
        void setX(const XUint x);
        void setY(const YUint y);
        void setZ(const ZUint z);

        bool isPositionValid(const XUint x, const ZUint z) const;
        bool isPositionValid(const Point3Uint& position) const;
    };

    typedef std::unique_ptr<Cursor> CursorPtr;
}
 #endif //WORLD_IMAKER_CURSOR_HPP
