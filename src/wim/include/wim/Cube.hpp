#ifndef WORLD_IMAKER_CUBE_HPP
#define WORLD_IMAKER_CUBE_HPP

#pragma once

#include <iostream>

#include "Colour.hpp"
#include "Displayable.hpp"
#include "Randomisable.hpp"


namespace wim
{
    ///Class for the structural Cube
    /*Will not be Displayed directly
    * But rather through the CubeStack class
     */
    class Cube : public Displayable //Needs to inherit Displayable as public in order to cast it as such when rendering.
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

        DisplayPattern getDisplayPattern() const override {return DisplayPattern::FULL_CUBE;}

        friend std::ostream& operator<<(std::ostream& out, const Cube& cube);

    };
    inline std::ostream& operator<<(std::ostream& out, const Cube& cube) {return out << cube._colour;}

}

#endif //WORLD_IMAKER_CUBE_HPP
