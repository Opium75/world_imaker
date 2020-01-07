//
// Created by piptouque on 29/12/2019.
//

#include "wim/Cursor.hpp"

#include <algorithm>

namespace wim
{

    static constexpr FloatType DEFAULT_CURSOR_COLOUR[] = {0.1f, 0.7f, 0.8f};



    Cursor::Cursor(const WorldPtr& world):
        Displayable(Colour(DEFAULT_CURSOR_COLOUR)), _world(world),
        _selection(std::make_unique<Selection>())
    {

    }

    bool Cursor::getHoveredCubePtr(CubePtr& cubePtr) const
    {
        return _world->findCube(cubePtr, _position);

    }

    void Cursor::selectHoveredCube() const
    {
        CubePtr cubePtr;
        SelectablePtr selectablePtr;
        if( this->getHoveredCubePtr(cubePtr) )
        {
            selectablePtr = cubePtr;
            _selection->select( selectablePtr);
        }
    }

    void Cursor::deselectHoveredCube() const
    {
        CubePtr cubePtr;
        SelectablePtr selectablePtr;
        if( this->getHoveredCubePtr(cubePtr) )
        {
            selectablePtr = cubePtr;
            _selection->deselect( selectablePtr);
        }
    }

    void Cursor::moveSelectedCube() const
    {
        CubePtr cubePtr;
        //Only if there is a single cube selected
        if( _selection->getNumber() == 1 )
        {
            _world->swapSpaces(_position, _selection->selected(0)->position());
            //deselecting.
            _selection->deselect(0);
        }
    }

    void Cursor::addHoveredCube(const Cube& cube) const
    {
        if( !this->isOccupied(_position) )
        {
            _world->add(cube, _position);
        }
    }

    void Cursor::eraseHoveredCube() const
    {
        if( this->isOccupied(_position) )
        {
            _world->erase(_position);
        }
    }

    void Cursor::extrudeHoveredCube() const
    {
        if( !this->isHoveredHigherStackEmpty() )
            _world->extrude(_position);
    }

    void Cursor::digHoveredCube() const
    {
        if( !this->isHoveredHigherStackEmpty() )
            _world->dig(_position);
    }

    bool Cursor::isOccupied(const Point3Uint& position) const
    {
        return _world->isOccupied(position);
    }

    DisplayPattern Cursor::getDisplayPattern() const
    {
        return DisplayPattern::WIREFRAME_CUBE;
    }

    bool Cursor::isHoveredHigherStackEmpty() const
    {
       return _world->isHigherStackEmpty(_position.x(), _position.y(), _position.z());
    }


    bool Cursor::isHoveredLowerStackEmpty() const
    {
        return _world->isLowerStackEmpty(_position.x(), _position.y(), _position.z());
    }

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

    void Cursor::clearSelected() const
    {
        _selection->clearSelected();
    }
    void Cursor::clearDeleted() const
    {
        _selection->clearDeleted();
    }

    const Point3Uint& Cursor::getPosition() const
    {
        return _position;
    }



}
