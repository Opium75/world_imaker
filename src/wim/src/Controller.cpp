//
// Created by piptouque on 18/12/2019.
//

#include "../include/wim/Controller.hpp"

namespace wim {

    //Default initialisation.
    AbstractController::DisplayerPtr AbstractController::_displayer(nullptr);
    AbstractController::ModelPtr AbstractController::_model(nullptr);
    Application::ControllerPtr Application::_ctrl(nullptr);

    void DisplayController::runDisplay() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _displayer->displayAll(*_model);
        SDL_GL_SwapWindow(_displayer->getWindowPtr().get());
    }

    bool UIController::runInterface() const
    {
        bool loop = true;

        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            //ImGui does its thing
            ImGui_ImplSDL2_ProcessEvent(&e);

            switch(e.type)
            {
                case SDL_QUIT :
                    loop = false;
                    break;

                case SDL_KEYDOWN  :
                    //Fonction in Controller or switch and case ?
                    std::cout << "Ahaha" << std::endl;
                    break;

                case SDL_MOUSEMOTION :
                    //Get the position
                    break;

                case SDL_MOUSEWHEEL:

                case SDL_MOUSEBUTTONDOWN :
                    //
                    break;

                default :
                    std::cout << "e event :" << e.type << std::endl;
                    break;
            }
        }
        return loop;
    }

    bool MainController::runLoop() const
    {



        /** Display Controller */
        _dispCtrl.runDisplay();
        /** Controller user interface (managing input) **/
        bool  loop = _uiCtrl.runInterface();
        /** Cinbtroller for  calculating results **/
        _compCtrl.runCompute();


        return loop;
    }
    void MainController::runApp() const
    {
        /** ImGui INITIALISATION **/
        std::string glslVersion = std::string("#version 130");
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