//
// Created by piptouque on 15/11/2019.
//

#include "../include/CubeStack.hpp"

using namespace wim;

CubeFloor::CubeFloor(const Cube& c, const CubeFloor::FloorIndex floor) :  _cube(c), _floor(floor)
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

CubeFloor::FloorIndex CubeStack::insertFloor(const Cube& cube, CubeFloor::FloorIndex insertFloor, bool insertHigher)
{
    /**Assumes the stack is already sorted **/
    Stack::iterator it = _stack.begin();
    int comparison;
    /*Travelling the stack looking for the right place to insert*/
    while( it != _stack.end() )
    {
        comparison = it->compareFloors(insertFloor);
        if( comparison == 1 )
        {
            /* we found a higher floor, inserting below it, and call it a day. */
            _stack.insert(it, CubeFloor(cube, insertFloor));
            return insertFloor;
        }
        else if( comparison == 0 && !insertHigher )
        {
            //if floor already taken AND not allowing insertion on higher floors
            throw std::string("Attempting to insert a Cube on an occupied floor, forbidding insertion on higher floor.");
        }
        else if( comparison == 0 && insertHigher )
        {
            //if allowed, be trying again on the next floor
            ++insertFloor;
        }
        /* if insertFloor below current floor, we just move on to the next */
        ++it;
    }
    /* Getting here means that we reached the end of the stack.
     * We simply insert at the end
     */
    _stack.insert(it, CubeFloor(cube, insertFloor));
    return insertFloor;
}


CubeFloor::FloorIndex CubeStack::eraseFloor(CubeFloor::FloorIndex floor, bool eraseHigher)
{
    /** Assumes SORTED **/
    Stack::iterator it = _stack.begin();
    int comparison;
    while( it != _stack.end() )
    {
        comparison = it->compareFloors(floor);
        if( comparison == 0 )
        {
            /* we found the right floor, let's erase and return the index of the floor. */
            _stack.erase(it);
            return floor;
        }
        else if( (comparison == 1) && !eraseHigher )
        {
            /* we are already too high on the Stack,
             * and we can't erase the next highest,
             * so we throw
             */
            throw std::string("Attempting to erase  a free floor, forbidding erasing on higher floor.");

        }
        else if ( (comparison == 1) && eraseHigher )
        {
            ++floor;
        }
        /* nothing more to do if we are too low than climb up the stack */
        ++it;
    }
    /* we could not erase said floor, throwing. */
    throw std::string("Attempting to erase a free floor (stack may be empty).");
}