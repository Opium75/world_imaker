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
    public:
        Widgets() = default;
        Widgets(const glimac::SDLWindowManager::SDL_WindowPtr& window, const SDL_GLContext& glContext)
        {
            this->initWidgets(window, glContext);
        }

        ~Widgets()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
        }

        IGContextPtr getIGContext() {return _context;}

        void initWidgets(const glimac::SDLWindowManager::SDL_WindowPtr& window, const SDL_GLContext& glContext)
        {
            std::string glslVersion = std::string("#version 150");
            //Start-up imgui
            IMGUI_CHECKVERSION();
            _context = ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            (void) io;

            //style
            ImGui::StyleColorsDark();

            //init for SDL2 and OpenGL 3
            ImGui_ImplSDL2_InitForOpenGL(window.get(), glContext);
            ImGui_ImplOpenGL3_Init(glslVersion.c_str());
        }

        void showDemo(const glimac::SDLWindowManager::SDL_WindowPtr window) const
        {

            std::cout << "Contexte :" << ImGui::GetCurrentContext() << std::endl;
            ImGui::ShowDemoWindow();
        }

        void display(const Displayer &disp) const;
    };
}
#endif //WORLD_IMAKER_WIDGETS_HPP
