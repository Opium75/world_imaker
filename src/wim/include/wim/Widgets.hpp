//
// Created by piptouque on 02/12/2019.
//

#ifndef WORLD_IMAKER_WIDGETS_HPP
#define WORLD_IMAKER_WIDGETS_HPP

#pragma once

#include <string>

//#include <glimac/SDLWindowManager.hpp>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include <glimac/SDLWindowManager.hpp>
#include "Displayable.hpp"


namespace wim
{
    class Displayer;
    class Widgets:public Displayable
    {
    private:
        typedef ImGuiContext* IGContextPtr;
        IGContextPtr _context;
        ImGuiIO* _io;
    public:
        //Widgets() = default;
        Widgets(/*const glimac::SDLWindowManager::SDL_WindowPtr& window, const SDL_GLContext& glContext*/)
        {
            this->initWidgets(/*window, glContext*/);
        }

        ~Widgets()
        {
            /*ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::SetCurrentContext(_context);
            ImGui::DestroyContext();
             */
        }

        const IGContextPtr& getIGContext() const {return _context;}

        void initWidgets(/*const glimac::SDLWindowManager::SDL_WindowPtr& window, const SDL_GLContext& glContext*/)
        {
          /*std::string glslVersion = std::string("#version 150");
            //Start-up imgui
            IMGUI_CHECKVERSION();
            _context = ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void) io;

            //style
            ImGui::StyleColorsDark();
            io.Fonts->AddFontDefault();

            //init for SDL2 and OpenGL 3
            ImGui_ImplSDL2_InitForOpenGL(window.get(), glContext);
            ImGui_ImplOpenGL3_Init(glslVersion.c_str());
            */
        }

        void showDemo(const glimac::SDLWindowManager::SDL_WindowPtr& window/*, const SDL_GLContext& glContext*/) const
        {
           /*std::string glslVersion = std::string("#version 150");
            //Start-up imgui
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();

            //style
            ImGui::StyleColorsDark();

            //init for SDL2 and OpenGL 3
            ImGui_ImplSDL2_InitForOpenGL(window.get(), glContext);
            ImGui_ImplOpenGL3_Init(glslVersion.c_str());
            */
            //std::cout << "Contexte :" << ImGui::GetCurrentContext() << std::endl;
            ImGui::SetCurrentContext(this->getIGContext());
            ImGuiIO &io = ImGui::GetIO(); (void)io;
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame(window.get());
            ImGui::NewFrame();

            ImGui::ShowDemoWindow();

            /*
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
             */
        }

        void display(const Displayer &disp) const;
    };
}
#endif //WORLD_IMAKER_WIDGETS_HPP
