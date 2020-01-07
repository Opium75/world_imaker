//
// Created by piptouque on 15/11/2019.
//

#include "../include/wim/CubeStack.hpp"

namespace wim
{

    CubeFloor::CubeFloor(const Cube& c, const XUint x, const FloorIndex floor, const ZUint z) :
        _cubePtr(std::make_shared<Cube>(c, x,floor,z)), _floor(floor)
    {

    }


    CubeStack::CubeStack(const XUint x, const ZUint z) :
            _stack(), _x(x), _z(z), _base()
    {
    }

    int CubeFloor::compareFloors(const FloorIndex floor) const
    {
        if (_floor > floor)
            return 1;
        if (_floor < floor)
            return -1;
        return 0;
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


    FloorIndex CubeStack::insertFloor(const Cube &cube, FloorIndex insertFloor, bool insertHigher) {
        /**Assumes the stack is already sorted **/
        auto it = _stack.begin();
        int comparison;
        /*Travelling the stack looking for the right place to insert*/
        while (it != _stack.end()) {
            comparison = it->compareFloors(insertFloor);
            if (comparison == 1) {
                /* we found a higher floor, insert below it, and call it a day. */
                _stack.insert(it, CubeFloor(cube, _x, insertFloor,_z));
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
        _stack.insert(it, CubeFloor(cube, _x, insertFloor,_z));
        return insertFloor;
    }

    FloorIndex CubeStack::insertFloor(const CubeFloor &cubeFloor, bool insertHigher)
    {
        return this->insertFloor(cubeFloor.cube(), cubeFloor.floor(), insertHigher);
    }

    FloorIndex CubeStack::eraseFloor(FloorIndex floor, bool eraseHigher)
    {
        /** Assumes SORTED **/
        Stack::iterator it = _stack.begin();
        int comparison;
        while (it != _stack.end()) {
            comparison = it->compareFloors(floor);
            if (comparison == 0) {
                /* we found the right floor, let's erase and return the index of the floor. */
                _stack.erase(it);
                return floor;
            }
            else if ((comparison == 1) && !eraseHigher)
            {
                /* we are already too high on the Stack,
                 * and we can't erase the next highest,
                 * so we throw
                 */
                throw Exception(ExceptCode::OUT_OF_RANGE,1,"Attempting to erase a free floor, forbidding erasing on higher floor.");

            }
            else if ((comparison == 1) && eraseHigher) {
                ++floor;
            }
            /* nothing more to do if we are too low than climb up the stack */
            ++it;
        }
        /* we could not erase said floor, throwing. */
        throw Exception(ExceptCode::OUT_OF_RANGE,1, "Attempting to erase a free floor (stack may be empty.");
    }


    Cube& CubeStack::cube(const FloorIndex floor)
    {
        SizeInt cubeIndex;
        if( !findCube(cubeIndex, floor) )
            throw Exception(ExceptCode::OUT_OF_RANGE, 1, std::string("No cube at floor: ") + std::to_string(floor));
        return _stack.at(cubeIndex).cube();
    }

    bool CubeStack::findCube(SizeInt& index, const FloorIndex floor) const
    {
        SizeInt j = 0;
        for (const auto &cubeFloor : _stack)
        {
            switch(cubeFloor.compareFloors(floor))
            {
                case 0: //same floor
                    index = j;
                    return true;
                case 1:
                    return false;
                case -1:
                    break;
            }
            ++j;
        }
        return false;
    }

    bool CubeStack::findCube(CubePtr& cube, const FloorIndex floor) const
    {
        SizeInt cubeIndex;
        if( !this->findCube(cubeIndex, floor) )
            return false;
        cube = _stack.at(cubeIndex).cubePtr();
        return true;
    }


    bool CubeStack::isOccupied(const FloorIndex floor) const
    {
       SizeInt placeholder;
       return this->findCube(placeholder, floor);
    }

    bool CubeStack::isHigherStackEmpty(const FloorIndex floor) const
    {
        for(const auto& cubeFloor : this->_stack )
        {
            switch( cubeFloor.compareFloors(floor) )
            {
                case 0: case 1: //higher or equal
                    return false;
                case -1:
                    break;
            }
        }
        return true;
    }

    bool CubeStack::isLowerStackEmpty(const FloorIndex floor) const
    {
        for(const auto& cubeFloor : this->_stack )
        {
            switch( cubeFloor.compareFloors(floor) )
            {
                case 0: case -1: //higher or equal
                    return false;
                case 1:
                    break;
            }
        }
        return true;
    }

    void CubeStack::dig(const FloorIndex floor)
    {
        int comparison;
        auto it = _stack.end()-1;
        do {
            comparison = it->compareFloors(floor);
            if (comparison >= 0) //higher or on same floor
            {
                _stack.erase(std::next(it));
                return;
            }
            --it;
        } while (it != _stack.begin());
        //There was no cube higher than floor, error.
        throw Exception(ExceptCode::ILLIGAL, 1, "No cube to dig.");
    }

    void CubeStack::extrude(const FloorIndex floor)
    {
        if( this->isHigherStackEmpty(floor) )
        {
            throw Exception(ExceptCode::ILLIGAL, 1, "No cube to extrude.");
        }
       Cube cube;
       auto it = _stack.begin();
       while( it->floor() < floor)
       {
           if( it == _stack.end()-1)
           {
               cube = it->cube();
              _stack.insert(_stack.end(), CubeFloor(cube, this->x(), it->floor()+1, this->z()));
                return;
           }
           ++it;
       }
       while( it != _stack.end()-1 )
       {
           if( std::next(it)->floor() - it->floor() > 1)
           {
                cube = it->cube();
               _stack.insert(std::next(it), CubeFloor(cube, this->x(), it->floor()+1, this->z()));
                return;
           }
           ++it;
       }
        _stack.insert(_stack.end(),CubeFloor(it->cube(), this->x(), it->floor()+1, this->z()));
    }

    void CubeStack::swapSpaces(CubeStack& cubeStack, const FloorIndex f1, const FloorIndex f2)
    {
        CubePtr c1,c2;
        bool firstOccupied = this->findCube(c1, f1);
        bool secondOccupied = cubeStack.findCube(c2, f2);
        if( firstOccupied && secondOccupied )
        {
            //if both spaces are occupied, we swap the cubes
            Cube temp = *c1;
            this->eraseFloor(f1, false);
            this->insertFloor(*c2, f1, false);
            cubeStack.eraseFloor(f2, false);
            cubeStack.insertFloor(temp, f2, false);
        }
        else if( firstOccupied )
        {
            //Then second space is not occupied.
            //Inserting first cube in second stack
            cubeStack.insertFloor(*c1, f2, false);
            this->eraseFloor(f1, false);
        }
        else if( secondOccupied )
        {
            this->insertFloor(*c2, f1, false);
            cubeStack.eraseFloor(f2, false);
        }
        //Not doing anything if both spaces are unoccupied.
    }

    CubeFloor CubeFloor::Random(const XUint x, const ZUint z, const FloorIndex min, const FloorIndex max)
    {
        FloorIndex floor;
        floor = RandomScalar<FloorIndex>(min, max);
        return CubeFloor(Cube::Random(), x, floor, z);
    }


    CubeStack CubeStack::Random(const XUint x, const ZUint z, const SizeInt maxNbFloors, const FloorIndex min, const FloorIndex max)
    {
        CubeStack cubeStack(x,z);
        FloorIndex insertedFloor;
        for (SizeInt i = 0; i < maxNbFloors; ++i)
        {
            /* Since the floors are random
             * we might have multiple cubes at the same floor,
             * so we insert higher in this case.
             * Note that the actual number of inserted floors can be lower than maxNbFloors.
             */
            insertedFloor = cubeStack.insertFloor(CubeFloor::Random(x, z, min, max), true);
            if (insertedFloor >= max)
                break;
        }
        return cubeStack;
    }


    //Under 300 lines: check.
}
