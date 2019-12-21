//
// Created by piptouque on 02/12/2019.
//

#ifndef WORLD_IMAKER_WIDGETMANAGER_HPP
#define WORLD_IMAKER_WIDGETMANAGER_HPP

#pragma once

#include <string>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include <glimac/SDLWindowManager.hpp>
#include "Displayable.hpp"


namespace wim
{
    class WidgetManager
    {
    private:
        typedef ImGuiContext* IGContextPtr;
        IGContextPtr _context;
        ImGuiIO* _io;
    public:
        //Widgets() = default;
        WidgetManager(/*const glimac::SDLWindowManager::SDL_WindowPtr& window, const SDL_GLContext& glContext*/)
        {
            this->initWidgets(/*window, glContext*/);
        }

        ~WidgetManager()
        {
            /*ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::SetCurrentContext(_context);
            ImGui::DestroyContext();
             */
        }

        const IGContextPtr& getIGContext() const {return _context;}
        const ImGuiIO* getIGIO() const {return _io;}

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

    void showDemo(/*const glimac::SDLWindowManager::SDL_WindowPtr& window, const SDL_GLContext& glContext*/) const
        {
            ImGui::ShowDemoWindow();
        };
    };
}
#endif //WORLD_IMAKER_WIDGETMANAGER_HPP
