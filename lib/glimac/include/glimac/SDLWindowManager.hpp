#pragma once

#include <memory>
#include <cstdint>
#include <iostream>
#include <SDL2/SDL.h>

//to avoid linking error
#undef main

#include "glm.hpp"

namespace glimac {

    /* todo: Migrate to SDL2 !! */
    class WindowDeleter {
        /* We have use a custom destructor,
        * and so specify what action to perform
        * (destroy window) as template param during the initialisation
        * when deleting the object.
         * But we can only use a type as param,
         * thus this class.
        */
    public:
        WindowDeleter() = default;
        ~WindowDeleter() = default;
        inline void operator()(SDL_Window* window) {SDL_DestroyWindow(window);}
    };
class SDLWindowManager {
private:
    typedef std::shared_ptr<SDL_Window> SDL_WindowPtr;
    SDL_WindowPtr _window;
    SDL_GLContext _context;

public:
    SDLWindowManager(uint32_t width, uint32_t height, const char* title);

    ~SDLWindowManager();

    bool pollEvent(SDL_Event& e);

    bool isKeyPressed(SDL_Keycode key) const;

    // button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
    bool isMouseButtonPressed(uint32_t button) const;

    glm::ivec2 getMousePosition() const;

    void swapBuffers();

    // Return the time in seconds
    float getTime() const;
};

}
