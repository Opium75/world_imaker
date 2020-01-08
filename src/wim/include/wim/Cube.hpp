#ifndef WORLD_IMAKER_CUBE_HPP
#define WORLD_IMAKER_CUBE_HPP

#pragma once

#include <iostream>
#include <memory>

#include "Types.hpp"

#include "Material.hpp"

#include "Displayable.hpp"
#include "Selectable.hpp"
#include "RBF.hpp"


namespace wim
{

    class Cube;
    typedef RBF<Cube, XUint, FloatType> CubeRBF;
    typedef RBFPtr<Cube, XUint, FloatType> CubeRBFPtr;
    ///Class for the structural Cube
    /*Will not be Displayed directly
    * But rather through the CubeStack class
     */
    class Cube : public Displayable, public Selectable //Needs to inherit Displayable as public in order to cast it as such when rendering.
    {
    private:
        //No need for radius since every cube in the grid is the same size
        //inherits Material from Displayable.
        //Inherits Posistion from Slectiable
    public:
        Cube() = default;
        Cube(const Material& material, const SizeInt textureIndex=0);
        Cube(const Cube& cube, const XUint x, const YUint floor, const ZUint z);
        Cube(const Cube& cube) = default;
        ~Cube() = default;

        Cube& operator=(const Cube& cube) = default;
        //Two overloaded operators used in procedural generation.
        Cube operator+(const Cube& cube) const;
        Cube& operator+=(const Cube& cube);
        Cube& operator*(const FloatType alpha);
        Cube& operator*=(const FloatType alpha);

        void swap(Cube& cube);

        static Cube Random();

        //Interface method from Selectable
        //From Displayable
        DisplayPattern getDisplayPattern() const override;

        friend std::ostream& operator<<(std::ostream& out, const Cube& cube);
        //friend void interpolate(Cube& cube, const Point3Uint& position);
    };

    inline std::ostream& operator<<(std::ostream& out, const Cube& cube)
    {
        return out << cube._material;
    }

    typedef std::shared_ptr<Cube> CubePtr;
}

#endif //WORLD_IMAKER_CUBE_HPP
