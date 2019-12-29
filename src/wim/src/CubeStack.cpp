//
// Created by piptouque on 15/11/2019.
//

#include "../include/wim/CubeStack.hpp"

namespace wim
{

    CubeFloor::CubeFloor(const Cube &c, const CubeFloor::FloorIndex floor) : _cube(c), _floor(floor) {

    }

    CubeFloor& CubeFloor::operator=(CubeFloor cFloor)
    {
        std::swap(*this, cFloor);
        return *this;
    }

    CubeStack::CubeStack(const CubeStack &cubeStack) : _stack(cubeStack._stack) {

    }

    Cube &CubeStack::topCube() {
        if (_stack.empty())
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Trying to access content of empty stack.");
        else
            return _stack.back().cube();
    }

    const Cube &CubeStack::topCube() const {
        if (_stack.empty())
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, "Trying to access content of empty stack.");
        else
            return _stack.back().cube();
    }

    CubeStack& CubeStack::operator=(CubeStack cubeStack)
    {
       std::swap(_stack, cubeStack._stack);
       return *this;
    }


    CubeFloor::FloorIndex CubeStack::insertFloor(const Cube &cube, CubeFloor::FloorIndex insertFloor, bool insertHigher) {
        /**Assumes the stack is already sorted **/
        auto it = _stack.begin();
        int comparison;
        /*Travelling the stack looking for the right place to insert*/
        while (it != _stack.end()) {
            comparison = it->compareFloors(insertFloor);
            if (comparison == 1) {
                /* we found a higher floor, insert below it, and call it a day. */
                _stack.insert(it, CubeFloor(cube, insertFloor));
                return insertFloor;
            } else if (comparison == 0 && !insertHigher) {
                //if floor already taken AND not allowing insertion on higher floors
                throw Exception(ExceptCode::OUT_OF_RANGE,1,"Attempting to insert a Cube on an occupied floor, forbidding insertion on higher floor.");
            } else if (comparison == 0 && insertHigher) {
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

    CubeFloor::FloorIndex CubeStack::insertFloor(const CubeFloor &cubeFloor, bool insertHigher) {
        return this->insertFloor(cubeFloor.cube(), cubeFloor.floor(), insertHigher);
    }


    CubeFloor::FloorIndex CubeStack::eraseFloor(CubeFloor::FloorIndex floor, bool eraseHigher) {
        /** Assumes SORTED **/
        Stack::iterator it = _stack.begin();
        int comparison;
        while (it != _stack.end()) {
            comparison = it->compareFloors(floor);
            if (comparison == 0) {
                /* we found the right floor, let's erase and return the index of the floor. */
                _stack.erase(it);
                return floor;
            } else if ((comparison == 1) && !eraseHigher) {
                /* we are already too high on the Stack,
                 * and we can't erase the next highest,
                 * so we throw
                 */
                throw Exception(ExceptCode::OUT_OF_RANGE,1,"Attempting to erase a free floor, forbidding erasing on higher floor.");

            } else if ((comparison == 1) && eraseHigher) {
                ++floor;
            }
            /* nothing more to do if we are too low than climb up the stack */
            ++it;
        }
        /* we could not erase said floor, throwing. */
        throw Exception(ExceptCode::OUT_OF_RANGE,1, "Attempting to erase a free floor (stack may be empty.");
    }

    CubeFloor CubeFloor::Random(const FloorIndex min, const FloorIndex max) {
        FloorIndex floor;
        floor = RandomScalar(min, max);
        return CubeFloor(Cube::Random(), floor);
    }

    CubeFloor CubeFloor::Random(const FloorIndex max) {
        return CubeFloor::Random(0, max);
    }

    CubeStack
    CubeStack::Random(const SizeInt maxNbFloors, const CubeFloor::FloorIndex min, const CubeFloor::FloorIndex max) {
        CubeStack cubeStack;
        CubeFloor::FloorIndex insertedFloor;
        for (SizeInt i = 0; i < maxNbFloors; ++i) {
            /* Since the floors are random
             * we might have multiple cubes at the same floor,
             * so we insert higher in this case.
             * Note that the actual number of inserted floors can be lower than maxNbFloors.
             */
            insertedFloor = cubeStack.insertFloor(CubeFloor::Random(min, max), true);
            if (insertedFloor >= max)
                break;
        }
        return cubeStack;
    }

    CubeStack
    CubeStack::Random(const SizeInt maxNbFloors, const CubeFloor::FloorIndex max) {
        return CubeStack::Random(maxNbFloors, 0, max);
    }

}
