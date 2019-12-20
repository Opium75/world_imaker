//
// Created by piptouque on 25/11/2019.
//

//Already includes Cube, CubeStack, CubeWorld headers.
#include "../include/wim/Displayer.hpp"


namespace wim {


    void Cube::display(const Displayer &disp) const
    {
        return disp.display(*this);
    }

    void CubeStack::display(const Displayer &disp) const
    {
        return disp.display(*this);
    }

    void CubeWorld::display(const Displayer &disp) const
    {
        return disp.display(*this);
    }

    void WidgetManager::display(const Displayer &disp) const
    {
        disp.display(*this);
    };

    void Displayer::display(const Cube &cube) const
    {
       //todo: Add cube to rendering stack
        std::cout << cube << std::endl;
    }

    void Displayer::display(const CubeStack &stack) const
    {
        std::cout << stack << std::endl;
    }

    void Displayer::display(const CubeWorld &world) const
    {
        std::cout << world(0, 0) << std::endl;
    }

    void Displayer::display(const WidgetManager &widgets) const
    {
        /* */
        /*
        ImGui::SetCurrentContext(widget.getIGContext());
        ImGuiIO &io = ImGui::GetIO(); (void)io;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(_manager->getWindowPtr().get());
        ImGui::NewFrame();

        widget.showDemo();
*/
        widgets.showDemo(/*_manager->getWindowPtr(), _manager->getGlContext()*/);
        /** ImGuiRendering **/
        /*
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
         */
    }



    void Displayer::displayAll() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(this->getWindowPtr().get());
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();
        ImGui::Begin("T'as vu ?");
        ImGui::End();

        this->display(_widgets);

        ImGui::Render();
        glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(this->getWindowPtr().get());
    }

    void Displayer::initDisplay(/*const char* appPath*/)
    {

   /*
        //Loading shaders according to conf file in resources/shaders
        _shaders = ShaderManager();
        std::cout << appPath << std::endl;
        //for now, we use only one set of shaders:
*/
        //init Imgui ? Nope, gets done befor by Controller.
        //_widget = Widgets(/*_manager.get()->getWindowPtr(), _manager.get()->getGlContext()*/);


    }
}
