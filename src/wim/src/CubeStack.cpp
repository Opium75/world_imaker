//
// Created by piptouque on 15/11/2019.
//

#include "../include/CubeStack.hpp"

using namespace wim;

CubeFloor::CubeFloor(const Cube& c, const CubeFloor::IndexFloor floor) :  _cube(c), _floor(floor)
{
    
}

CubeStack::CubeStack(const CubeStack& cubeStack) : _stack(cubeStack._stack)
{

}

Cube& CubeStack::topCube()
{
    if( _stack.empty() )
        throw std::string("Trying to access content of empty stack.");
    else
        return _stack.back().cube();
}

const Cube& CubeStack::topCube() const
{
    if( _stack.empty() )
        throw std::string("Trying to access content of empty stack.");
    else
        return _stack.back().cube();
}
