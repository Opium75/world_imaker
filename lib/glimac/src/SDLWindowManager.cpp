#include "glimac/SDLWindowManager.hpp"

namespace glimac {

SDLWindowManager::SDLWindowManager(uint32_t width, uint32_t height, const char* title) {
    if(0 != SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << SDL_GetError() << std::endl;
        return;
    }

   _window.reset(SDL_CreateWindow(
           title,
           SDL_WINDOWPOS_UNDEFINED,
           SDL_WINDOWPOS_UNDEFINED,
           width,
           height,
           SDL_WINDOW_OPENGL
    ), WindowDeleter()
    );
    _context = SDL_GL_CreateContext(&*_window);
    SDL_GL_MakeCurrent(&*_window, &*_context);
}

    SDLWindowManager::~SDLWindowManager() {
        SDL_GL_DeleteContext(_context);
        //Destroying window by resetting the pointer (through WindowDeleter, see header.)
        _window.reset();
        SDL_Quit();
    }

    bool SDLWindowManager::pollEvent(SDL_Event& e) {
    return SDL_PollEvent(&e);
}

bool SDLWindowManager::isKeyPressed(SDL_Keycode key) const {
   //return SDL_GetKey(nullptr)[key];
   return false;
}

// button can SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
bool SDLWindowManager::isMouseButtonPressed(uint32_t button) const {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
}

glm::ivec2 SDLWindowManager::getMousePosition() const {
    glm::ivec2 mousePos;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    return mousePos;
}

void SDLWindowManager::swapBuffers() {
    //SDL_GL_Swa();
}

float SDLWindowManager::getTime() const {
    return 0.001f * SDL_GetTicks();
}

}
