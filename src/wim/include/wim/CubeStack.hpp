//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_CUBESTACK_HPP
#define WORLD_IMAKER_CUBESTACK_HPP

#pragma once

#include <stack>
#include <iostream>
#include <string>

#include "Exception.hpp"
#include "Randomisable.hpp"
#include "Cube.hpp"


namespace wim
{

    /* All right, bear with me here
     * I needed to have yet another class
     * so as not to insert the index attribute in Cube.
     * This class should offer a way to COMPARE the floors(étages)
     * of Cubes in a CubeStack
     */
    ///A container for a Cube with its index in a CubeStack
    class CubeFloor
    {
    public:
        typedef int FloorIndex;
    private:
        Cube _cube;
        FloorIndex _floor;
    public:
        CubeFloor() = default;
        CubeFloor(const Cube &c, const FloorIndex floor = -1);
        ~CubeFloor() = default;

        inline Cube &cube() { return _cube; };
        inline const Cube &cube() const { return _cube; };
        inline FloorIndex &floor() { return _floor; };
        inline FloorIndex floor() const { return _floor; };


        inline int compareFloors(const FloorIndex floor) const
        {
            if (_floor > floor)
                return 1;
            if (_floor < floor)
                return -1;
            return 0;
        }
        ///Return 1 if this Cube is on a higher floor than one given as argument, 0 if equal and -1 if lower
        inline int compareFloors(const CubeFloor &cFloor) const {return this->compareFloors(cFloor.floor());}

        CubeFloor& operator=(const CubeFloor &cFloor);

        /* convenient operators : FLOOR COMPARISON */
        ///Operator for comparison of floors, for Cube-related comparisons (Colours, etc.) see Cube Class
        inline bool operator>(const CubeFloor &cFloor) const { return (this->compareFloors(cFloor) == 1);}
        inline bool operator>=(const CubeFloor &cFloor) const { return (this->compareFloors(cFloor) >= 0);}
        inline bool operator==(const CubeFloor &cFloor) { return (this->compareFloors(cFloor) == 0);}


        static CubeFloor Random(const FloorIndex min, const FloorIndex max);
        static CubeFloor Random(const FloorIndex max);

    };

    ///A stack of CubeFloor-class objects, sorted according to their floors
    //In fact using a standard double-ended queue
    class CubeStack
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

        inline Stack& stack() {return _stack;}
        inline const Stack& stack() const {return _stack;}

        CubeStack& operator=(const CubeStack &cubeStack);

        ///Attempts to insert Cube at given floor in SORTED CubeStack
        ///If insertHigher is true, then the cube is inserted on the next available floor
        ///Returns actual floor of insertion on success
        ///Throws an exception on failure (only happens if insertHigher is false)
        CubeFloor::FloorIndex insertFloor(const Cube& cube, CubeFloor::FloorIndex floor, bool insertHigher = false);
        CubeFloor::FloorIndex insertFloor(const CubeFloor& cubeFloor, bool insertHigher = false);

        ///Attemps to erase content at given floor in SORTED CubeStack
        ///If eraseHigher is true, then attemps to erase the next occupied floor
        ///Returns actual floor of erasing on success
        ///Throws exceptions on failure
        CubeFloor::FloorIndex eraseFloor(CubeFloor::FloorIndex floor, bool eraseHigher = false);

        Cube& cube(const CubeFloor::FloorIndex floor)
        {
           for( auto& cubeFloor : _stack )
           {
               if( cubeFloor.floor() == floor )
                   return cubeFloor.cube();
               else if( cubeFloor.floor() > floor )
                   throw Exception(ExceptCode::OUT_OF_RANGE, 1, std::string("No cube at floor: ") + std::to_string(floor));
           }
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, std::string("No cube at floor: ") + std::to_string(floor));
        }


        static CubeStack Random(const size_t maxNbFloors, const CubeFloor::FloorIndex min, const CubeFloor::FloorIndex max);
        static CubeStack Random(const size_t maxNbFloors, const CubeFloor::FloorIndex max);

        friend std::ostream& operator<<(std::ostream& out, const CubeStack& cubeStack);
    };


    inline std::ostream& operator<<(std::ostream& out, const CubeStack& cubeStack)
    {
        CubeFloor::FloorIndex former=0;
        for(const auto& cubeFloor : cubeStack._stack )
        {
            for(CubeFloor::FloorIndex i=former; i<cubeFloor.floor(); ++i)
                out << " xxx "<<std::endl;
            out << cubeFloor.cube() << std::endl;
            former = cubeFloor.floor();
        }
        return out;
    }
}

#endif //WORLD_IMAKER_CUBESTACK_HPP
