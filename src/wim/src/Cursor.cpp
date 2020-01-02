//
// Created by piptouque on 29/12/2019.
//

#include "wim/Cursor.hpp"

#include <algorithm>

namespace wim
{
    void Cursor::setX(const XUint x)
    {
        _position.x() = std::min(x, this->getWorldWidth()-1);
    }
    void Cursor::setY(const YUint y)
    {
        /* NOT CHECKING Y-AXIS, SINCE IT IS DYNAMIC.*/
        _position.y() = y;
    }
    void Cursor::setZ(const ZUint z)
    {
        _position.z() = std::min(z, this->getWorldLength()-1);
    }

    void Cursor::moveX(const XInt delta)
    {
        XInt x =  std::max<XInt>(0, (XInt)_position.x()+delta);
        this->setX(x);
    }
    void Cursor::moveY(const YInt delta)
    {
        YInt y =  std::max<YInt>(0, (YInt)_position.y()+delta);
        this->setY(y);
    }
    void Cursor::moveZ(const ZInt delta)
    {
        ZInt z =  std::max<ZInt>(0, (ZInt)_position.z()+delta);
        this->setZ(z);
    }

    void Cursor::setPosition(const XUint x, const YUint y, const ZUint z)
    {
        if( isPositionValid(x,z) )
        {
            setX(x); setY(y); setZ(z);
        }
        else
        {

        }
    }

    void Cursor::setPosition(const Point3Uint& position)
    {
        this->setPosition(position.x(), position.y(), position.z());
    }

    bool Cursor::isPositionValid(const XUint x, const ZUint z) const
    {
        return x < this->getWorldWidth() && z < this->getWorldLength();
    }
    bool Cursor::isPositionValid(const Point3Uint& position) const
    {
        return isPositionValid(position.x(), position.z());
    }

    const Anchor& Cursor::getPosition() const
    {
        return _position;
    }
}
