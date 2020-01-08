
#include <wim/wim.hpp>

#include <iostream>
#include <cstdlib>

int main(int argc, char **argv) {
    wim::XUint worldWidth;
    wim::ZUint worldLength;
    const char* appPath = argv[0];
    if(argc>3)
    {
        worldWidth = std::atoi(argv[1]);
        worldLength = std::atoi(argv[2]);

    } else
    {
        worldWidth = 10;
        worldLength = 10;
    }


    wim::Application::init(appPath, worldWidth, worldLength);
    wim::Application::run();

    return EXIT_SUCCESS;

}