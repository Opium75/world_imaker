//
// Created by piptouque on 15/11/2019.
//

#ifndef WORLD_IMAKER_CUBESTACK_HPP
#define WORLD_IMAKER_CUBESTACK_HPP

#pragma once

#include <utility>
#include <deque>
#include <iostream>

#include "Types.hpp"
#include "Exception.hpp"
#include "Randomisable.hpp"
#include "Cube.hpp"
#include "Quad.hpp"

namespace wim
{

    /** I need to have yet another class
     * so as not to insert the index attribute in Cube.
     * This class should offer a way to COMPARE the floors(étages)
     * of Cubes in a CubeStack
     */
    typedef YUint FloorIndex;
    ///brief: A container for a Cube with its index in a CubeStack
    class CubeFloor
    {
    private:
        CubePtr _cubePtr;
        FloorIndex _floor;
    public:
        CubeFloor() = default;
        CubeFloor(const Cube& c, const XUint x, const FloorIndex floor, const ZUint z);
        CubeFloor(const CubeFloor& cFloor) = default;
        ~CubeFloor() = default;

        CubeFloor& operator=(const CubeFloor& cFloor) = default;

        inline CubePtr& cubePtr() {return _cubePtr;}
        inline const CubePtr& cubePtr() const {return _cubePtr;}
        inline Cube &cube() { return *_cubePtr; }
        inline const Cube &cube() const {return *_cubePtr; }
        inline FloorIndex &floor() { return _floor; }
        inline FloorIndex floor() const { return _floor; }

        inline XUint x() const {return _cubePtr->x();}
        inline ZUint z() const {return _cubePtr->z();}

        ///brief: returns 1 if the current floor is higher, 0 if same, -1 if lower
        int compareFloors(const FloorIndex floor) const;

        ///Return 1 if this Cube is on a higher floor than one given as argument, 0 if equal and -1 if lower
        inline int compareFloors(const CubeFloor &cFloor) const {return this->compareFloors(cFloor.floor());}

        /* convenient operators : FLOOR COMPARISON */
        ///Operator for comparison of floors, for Cube-related comparisons (Colours, etc.) see Cube Class
        inline bool operator>(const CubeFloor &cFloor) const { return (this->compareFloors(cFloor) == 1);}
        inline bool operator>=(const CubeFloor &cFloor) const { return (this->compareFloors(cFloor) >= 0);}
        inline bool operator==(const CubeFloor &cFloor) { return (this->compareFloors(cFloor) == 0);}


        static CubeFloor Random(const XUint x, const ZUint z, const FloorIndex min, const FloorIndex max);

    };



    ///A stack of CubeFloor-class objects, sorted according to their floors
    //In fact using a standard double-ended queue
    class CubeStack
    {
    private:
        typedef std::deque<CubeFloor> Stack;
        Stack _stack;
        XUint _x; ZUint _z;
        BaseQuad _base;
    public:
        CubeStack() = default;
        CubeStack(const XUint x, const ZUint z);
        CubeStack(const CubeStack& cubeStack) = default;
        ~CubeStack() = default;

        Cube& topCube();
        const Cube& topCube() const;

        inline Stack& stack() {return _stack;}
        inline const Stack& stack() const {return _stack;}

        inline XUint x() const {return _x;}
        inline ZUint z() const {return _z;}
        inline const BaseQuad& base() const {return _base;}

        CubeStack& operator=(const CubeStack& cubeStack) = default;

        ///Attempts to insert Cube at given floor in SORTED CubeStack
        ///If insertHigher is true, then the cube is inserted on the next available floor
        ///Returns actual floor of insertion on success
        ///Throws an exception on failure (only happens if insertHigher is false)
        FloorIndex insertFloor(const Cube& cube, FloorIndex floor, bool insertHigher = false);
        FloorIndex insertFloor(const CubeFloor& cubeFloor, bool insertHigher = false);

        void extrude(const FloorIndex floor);
        void dig(const FloorIndex floor);
        ///Attemps to erase content at given floor in SORTED CubeStack
        ///If eraseHigher is true, then attemps to erase the next occupied floor
        ///Returns actual floor of erasing on success
        ///Throws exceptions on failure
        FloorIndex eraseFloor(FloorIndex floor, bool eraseHigher = false);

        Cube& cube(const FloorIndex floor);

        ///biref: No-exception version of cube()
        bool findCube(CubePtr &cube, const FloorIndex floor) const;
        bool isOccupied(const FloorIndex floor) const;
        bool isHigherStackEmpty(const FloorIndex floor) const;
        bool isLowerStackEmpty(const FloorIndex floor) const;


        void swapSpaces(CubeStack& cubeStack, const FloorIndex f1, const FloorIndex f2);

        static CubeStack Random(const XUint x, const ZUint z, const size_t maxNbFloors, const FloorIndex min, const FloorIndex max);

        friend std::ostream& operator<<(std::ostream& out, const CubeStack& cubeStack);

    private:
        bool findCube(SizeInt& index, const FloorIndex floor) const;
    };


    inline std::ostream& operator<<(std::ostream& out, const CubeStack& cubeStack)
    {
        FloorIndex former=0;
        for(const auto& cubeFloor : cubeStack._stack )
        {
            for(FloorIndex i=former; i<cubeFloor.floor(); ++i)
                out << " xxx "<<std::endl;
            out << cubeFloor.cube() << std::endl;
            former = cubeFloor.floor();
        }
        return out;
    }
}

#endif //WORLD_IMAKER_CUBESTACK_HPP
