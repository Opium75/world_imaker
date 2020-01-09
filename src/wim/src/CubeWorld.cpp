//
// Created by piptouque on 19/11/2019.
//

#include "../include/wim/CubeWorld.hpp"

#include <algorithm>
#include <utility>

namespace wim
{
    CubeWorld::CubeWorld(const XUint width, const ZUint length) :
        _matrix(width,length)
    {
        for (XUint x = 0; x < width; ++x)
        {
            for (ZUint z = 0; z < length; ++z)
            {
                CubeStack& stack = this->operator()(x,z);
                stack = CubeStack(x,z);
            }
        }
    }

    YUint CubeWorld::getHeight() const
    {
        YUint max = 0;
        for(XUint x=0; x<this->getWidth(); ++x)
        {
            for(ZUint z=0; z<this->getLength(); ++z)
            {
                max = std::max(max, this->operator()(x,z).getHeight());
            }
        }
        return max;
    }


    Cube& CubeWorld::operator()(const XUint x, const YUint y, const ZUint z)
    {
        try
        {
            return this->operator()(x,z).cube(y);
        }
        catch(Exception& e)
        {
            e.addMessageHead(std::string("In  CubeStack (")+std::to_string(x)+", "+std::to_string(y)+") :");
            throw;
        }
    }


    Cube& CubeWorld::operator()(const Point3Uint& position)
    {
        return this->operator()(position.x(), position.y(), position.z());
    }



    CubeWorld& CubeWorld::operator=(CubeWorld world)
    {
        std::swap(_matrix, world._matrix);
        return *this;
    }

    bool CubeWorld::findCube(CubePtr& cubePtr, const Point3Uint& position)
    {

        CubeStack& stack = this->operator()(position.x(), position.z());
        return stack.findCube(cubePtr, position.y());
    }


    bool CubeWorld::isOccupied(const Point3Uint& position) const
    {
        return this->operator()(position.x(), position.z()).isOccupied(position.y());
    }


    void CubeWorld::add(const Cube& cube, const Point3Uint& position)
    {
        CubeStack& stack = this->operator()(position.x(), position.z());
        if( stack.isOccupied(position.y()) )
        {
            throw Exception(ExceptCode::ILLIGAL, 1, "Space already occupied for cube adding: " + position.toString());
        }
        stack.insertFloor(cube, position.y(), false);
    }

    void CubeWorld::erase(const Point3Uint& position)
    {
        CubeStack& stack = this->operator()(position.x(), position.z());
        if( !stack.isOccupied(position.y()) )
        {
            throw Exception(ExceptCode::ILLIGAL, 1, "Space not occupied for cube deletion: " + position.toString());
        }
        stack.eraseFloor(position.y(), false);
    }

    void CubeWorld::extrude(const Point3Uint &position)
    {

        CubeStack& stack = this->operator()(position.x(), position.z());
        stack.extrude(position.y());
    }

    void CubeWorld::dig(const Point3Uint &position)
    {

        CubeStack& stack = this->operator()(position.x(), position.z());
        stack.dig(position.y());
    }

    void CubeWorld::swapSpaces(const Point3Uint &position1, const Point3Uint &position2)
    {
        CubeStack& stack1 = this->operator()(position1.x(), position1.z());
        CubeStack& stack2 = this->operator()(position2.x(), position2.z());

        stack1.swapSpaces(stack2, position1.y(), position2.y());

    }

    bool CubeWorld::isHigherStackEmpty(const XUint x, const FloorIndex floor, const ZUint z) const
    {
        return this->operator()(x,z).isHigherStackEmpty(floor);
    }

    bool CubeWorld::isLowerStackEmpty(const XUint x, const FloorIndex floor, const ZUint z) const
    {
        return this->operator()(x,z).isLowerStackEmpty(floor);
    }

    CubeWorld CubeWorld::Random(const XUint width, const ZUint length) {
        YUint height = (width + length) /2;
        CubeWorld world(width, length);
        for(XUint x = 0; x < width; ++x)
        {
            for(ZUint z = 0; z < length; ++z)
            {
                world(x, z) = CubeStack::Random(x,z, height, 0, height);
            }
        }
        return world;
    }


    CubeWorld CubeWorld::Procedural(const XUint width, const YUint height, const ZUint length, const SelectionPtr& selection, ProceduralGeneratorPtr& generator, const RadialMethod method)
    {
        CubeWorld world(width, length);
        //updating generator with selection
        generator->build(selection, method);
        //getting generated RBF
        CubeRBF &rbf = generator->getCubeRBF();
        for(XUint x=0; x<width; ++x)
        {
            for(ZUint z=0; z<length; ++z)
            {
               world(x,z) = CubeStack::Procedural(x,z,height, rbf);
            }
        }
        return world;
    }
}