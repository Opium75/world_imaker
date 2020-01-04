
#include <wim/wim.hpp>

#include <iostream>

int main(int argc, char **argv) {
    if(argc<1)
    {
        /*that won't happen, but whatever. I need to use argc somehow
        *  so I don't get the unused variable warning (treated as an error).
         */
        throw wim::Exception(wim::ExceptCode::CATASTROPHIC_FAILURE, 42, "All your bases are belong to us!");
    }
    const char* appPath = argv[0];
    const wim::XUint worldWidth = 3;
    const wim::ZUint worldLength = 3;


    wim::Application::init(appPath, worldWidth, worldLength);
    wim::Application::run();
/*
    wim::Vec3D p1(1,-1, 0);
    wim::Point3Int p2(1,3,3);
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
*/
    return EXIT_SUCCESS;

}