#include <iostream>

#include "./src/wim/include/Vec3D.hpp"
#include "./src/wim/include/Colour.hpp"
#include "./src/wim/include/CubeWorld.hpp"

int main() {

    wim::Vec3D p1(1,-1, 0);
    wim::Point3D p2(1,3,3);
    std::cout << "Point 1 : " << p1 << std::endl;
    std::cout << "Point 2 : " << p2 << std::endl;
    std::cout << "Somme de deux points : " << p1 + p2 << std::endl;

    wim::Colour c1;
    wim::Colour c2(2,-1, 0.2);
    std::cout << "Couleur 1 : " << c1 << std::endl;
    std::cout << "Couleur 2 : " << c2 << std::endl;
    std::cout << "Moyenne de deux couleurs : " << c1.average(c2) << std::endl;
    return EXIT_SUCCESS;

}