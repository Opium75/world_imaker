#ifndef WORLD_IMAKER_CUBE_HPP
#define WORLD_IMAKER_CUBE_HPP

#pragma once

#include "Colour.hpp"
#include "Displayable.hpp"



namespace wim
{
    ///Class for the structural Cube
    /*Will not be Displayed directly
    * But rather through the CubeStack class
     */
    class Cube : protected Displayable, protected Randomisable
    {
    private:
        //No need for radius since every cube in the grid is the same size
        Colour _colour;
    public:
        Cube() = default;
        Cube(const Colour& colour);
        Cube(const Cube& cube);
        ~Cube() = default;

    protected:
        //inherited from Displayable
        void display() const {};



    };

}

#endif //WORLD_IMAKER_CUBE_HPP
