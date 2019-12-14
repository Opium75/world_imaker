#ifndef WORLD_IMAKER_CUBE_HPP
#define WORLD_IMAKER_CUBE_HPP

#pragma once

#include <iostream>

#include "Colour.hpp"
#include "Displayable.hpp"
#include "Randomisable.hpp"


namespace wim
{

    class Displayer;
    ///Class for the structural Cube
    /*Will not be Displayed directly
    * But rather through the CubeStack class
     */
    class Cube : protected Displayable //protected Randomisable<Cube, double>
    {
    private:
        //No need for radius since every cube in the grid is the same size
        Colour _colour;
    public:
        Cube() = default;
        Cube(const Colour& colour);
        Cube(const Cube& cube);
        ~Cube() = default;

        Cube& operator=(const Cube& cube);

        static Cube Random();

        friend std::ostream& operator<<(std::ostream& out, const Cube& cube);

    protected:
        //inherited from Displayable
        //Defined in Displayer source file
        void display(const Displayer& disp) const;
    };

    inline std::ostream& operator<<(std::ostream& out, const Cube& cube) {return out << cube._colour;}
}

#endif //WORLD_IMAKER_CUBE_HPP
