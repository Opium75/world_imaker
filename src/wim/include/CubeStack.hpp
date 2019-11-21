//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_CUBESTACK_HPP
#define WORLD_IMAKER_CUBESTACK_HPP

#pragma once

#include <stack>
#include "Cube.hpp"

namespace wim
{
    /* All right, bear with me here
     * I needed to have yet another class
     * so as not to insert the index attribute in Cube.
     * This class should offer a way to COMPARE the floor(étage)
     * of each cube in a CubeStack
     */
    ///A container for a Cube with its index in a CubeStack
    class CubeFloor
    {
    private:
        Cube _cube;
        typedef int IndexFloor;
        IndexFloor _floor;
    public:
        CubeFloor() = default;
        CubeFloor(const Cube& c, const IndexFloor floor=-1);
        ~CubeFloor() = default;
        ///Return 1 if this Cube is on a higher floor than one given as argument, 0 if equal and -1 if lower
        inline int compareFloors(const CubeFloor& cFloor) const
        {

            if( _floor > cFloor._floor )
                return 1;
            if( _floor < cFloor._floor )
                return -1;
            return 0;
        }

        /* convenient operators : FLOOR COMPARISON */
        ///Operator for comparison of floors, for Cube-related comparisons (Colours, etc.) see Cube Class
        inline bool operator>(const CubeFloor& cFloor) const
        {
            return (this->compareFloors(cFloor) == 1);
        };
        inline bool operator>=(const CubeFloor& cFloor) const
        {
            return (this->compareFloors(cFloor) >= 0);
        };
        inline bool operator==(const CubeFloor& cFloor)
        {
            return (this->compareFloors(cFloor) == 0);
        }
    };
    ///A stack of Cube-class objects
    //In fact using a standard double-ended queue
    class CubeStack : protected Displayable
    {
    private:
        typedef std::deque<CubeFloor> Stack;
        Stack _stack;
    public:
        CubeStack() = default;
        CubeStack(const CubeStack& cubeStack);
        ~CubeStack() = default;

        Cube& topCube();
        const Cube& topCube() const;

        //again, CubeStack will be Displayed through CubeWorld
        void display() const {};
    };
}

#endif //WORLD_IMAKER_CUBESTACK_HPP
