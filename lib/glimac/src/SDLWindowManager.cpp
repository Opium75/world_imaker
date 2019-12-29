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
           (SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI)
    ), WindowDeleter()
    );
    _context = SDL_GL_CreateContext(_window.get());
    SDL_GL_MakeCurrent(_window.get(), _context);
    SDL_GL_SetSwapInterval(1); //for vsync (?)    //SDL init done in initialisation list

    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError)
    {
       //throw Exception(ExceptCode::INIT_ERROR, 1, "Could not initialise glew.");
    }

    //FOR 3d
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version:   " << glewGetString(GLEW_VERSION) << std::endl;
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
   return SDL_GetKeyboardState(nullptr)[key];
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
    SDL_GL_SwapWindow(_window.get());
}

float SDLWindowManager::getTime() const {
    return 0.001f * SDL_GetTicks();
}

}
