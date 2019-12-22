//
// Created by piptouque on 02/12/2019.
//

#ifndef WORLD_IMAKER_WIDGETMANAGER_HPP
#define WORLD_IMAKER_WIDGETMANAGER_HPP

#pragma once

#include <string>

#include <imgui.h>

#include <glimac/SDLWindowManager.hpp>
#include "Displayable.hpp"


namespace wim
{
    class WidgetManager
    {
    private:
    public:
        WidgetManager() = default;
        ~WidgetManager() = default;


    void showDemo() const
        {
            ImGui::ShowDemoWindow();
        };
    };
}
#endif //WORLD_IMAKER_WIDGETMANAGER_HPP
