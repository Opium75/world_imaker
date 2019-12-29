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
        Point3Int _position;
        WorldPtr _world;
        SelectablePtr _selected;
    public:
        Cursor(const WorldPtr& world) : Displayable(), _world(world) {}
        ~Cursor() = default;

        void setX(const XUint x);
        void setY(const YUint y);
        void setZ(const ZUint z);

        void moveX(const Xint delta);
        void moveY(const Yint delta);
        void moveZ(const Zint delta);

        void setPosition(const XUint x, const YUint y, const ZUint z);
        inline void setPosition(const Point3Int& position) {this->setPosition(position.x(), position.y(), position.z());}
        const Point3Int& getPosition() const;

        inline XUint getWorldWidth() const {return _world->getWidth();}
        inline YUint getWorldLength() const {return _world->getLength();}

        DisplayPattern getDisplayPattern() const override
        {
            return DisplayPattern::WIREFRAME_CUBE;
        }
    };

    typedef std::unique_ptr<Cursor> CursorPtr;
}
 #endif //WORLD_IMAKER_CURSOR_HPP
