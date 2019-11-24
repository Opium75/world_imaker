#include <iostream>

#include "./src/wim/include/Vec3D.hpp"
#include "./src/wim/include/Colour.hpp"
#include "./src/wim/include/CubeWorld.hpp"

int main() {

    wim::Vec3D p1(1,-1, 0);
    wim::Point3D p2(1,3,3);
    wim::Vec3D v1 = wim::Vec3D::Random();
    wim::Vec3D v2 = wim::Vec3D::Random(10, 100);
    std::cout << "Point 1 : " << p1 << std::endl;
    std::cout << "Point 2 : " << p2 << std::endl;
    std::cout << "Vecteur aléatoire 1 :" << v1<< std::endl;
    std::cout << "Vecteur aléatoire 2 :" << v2 << std::endl;
    std::cout << "Somme de deux points : " << p1 + p2 << std::endl;

    wim::Colour c1;
    wim::Colour c2(2,-1, 0.2);
    std::cout << "Couleur 1 : " << c1 << std::endl;
    std::cout << "Couleur 2 : " << c2 << std::endl;
    std::cout << "Moyenne de deux couleurs : " << c1.average(c2) << std::endl;

    wim::CubeStack s1 = wim::CubeStack::Random(4, 5);
    wim::CubeStack s2 = wim::CubeStack::Random(2, 4);
    std::cout << "Pile de cubes aléatoires 1 : " << std::endl;
    std::cout << s1 << std::endl;
    std::cout << "Pile de cubes aléatoires 2 : " << std::endl;
    std::cout << s2 << std::endl;

    return EXIT_SUCCESS;

}