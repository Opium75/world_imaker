//
// Created by piptouque on 18/12/2019.
//

#include "../include/wim/Controller.hpp"

namespace wim {

    //Default initialisation.
    ModelPtr AbstractController::_model(nullptr);
    DisplayerPtr AbstractController::_displayer(nullptr);
    InterfacePtr AbstractController::_interface(nullptr);

    Application::ControllerPtr Application::_ctrl(nullptr);

    void DisplayController::runDisplay() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _displayer->displayAll(*_model);
        _displayer->windowManager()->swapBuffers();
    }

    bool InterfaceController::runInterface() const
    {
        return _interface->run();
    }

    bool MainController::runLoop() const
    {



        /** Display Controller */
        _dispCtrl.runDisplay();
        /** Controller user interface (managing input) **/
        bool  loop = _interCtrl.runInterface();
        /** Cinbtroller for  calculating results **/
        _compCtrl.runCompute();


        return loop;
    }
    void MainController::runApp() const
    {
        /** ImGui INITIALISATION **/
        std::string glslVersion = std::string("#version 150");
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        //Start-up imgui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        //style
        ImGui::StyleColorsDark();
        //init for SDL2 and OpenGL 3
        ImGui_ImplSDL2_InitForOpenGL(_dispCtrl.getWindowPtr().get(), _dispCtrl.getGLContext());
        ImGui_ImplOpenGL3_Init(glslVersion.c_str());

        /** RUNNING APPLICATION LOOP **/
        while( this->runLoop() );

        /** FREEING ImGui RESOURCES **/
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

    }

}