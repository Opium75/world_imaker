//
// Created by piptouque on 18/12/2019.
//

#include "../include/wim/Controller.hpp"

namespace wim {
    void DisplayController::runDisplay() const
    {
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(this->getWindowPtr().get());
        ImGui::NewFrame();
            //ImGui::ShowDemoWindow();
        ImGui::Begin("T'as vu ?");
        ImGui::End();

        //_disp.displayAll();
        ImGui::Render();
        glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(_disp.getWindowPtr().get());
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



                default :
                    break;
            }
        }
        return loop;
    }

    bool Controller::runLoop() const
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


        /** Display Controller */
        _dispCtrl.runDisplay();
        /** Controller user interface (managing input) **/
        bool  loop = _uiCtrl.runInterface();
        /** Cinbtroller for  calculating results **/
        _compCtrl.runCompute();

        /** FREEING ImGui RESOURCES **/
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        return loop;
    }


}