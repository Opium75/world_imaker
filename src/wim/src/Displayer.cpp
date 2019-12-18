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

    void Widgets::display(const Displayer &disp) const
    {
        disp.display(*this);
    };

    void Displayer::display(const Cube &cube) const
    {
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

    void Displayer::display(const Widgets &widget) const
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
        widget.showDemo(_manager->getWindowPtr()/*, _manager->getGlContext()*/);
        /** ImGuiRendering **/
        /*
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
         */
    }



    void Displayer::displayAll() const
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->display(_widget);
    }

    void Displayer::initDisplay(const char* appPath)
    {

        //Init SDLWIndowManager
        _manager = std::make_unique<glimac::SDLWindowManager>(
                       wim::DISP_WINDOW_WIDTH,
                       wim::DISP_WINDOW_HEIGHT,
                       wim::DISP_WINDOW_NAME
        );

        GLenum glewInitError = glewInit();
        if(GLEW_OK != glewInitError)
        {
            throw Exception(ExceptCode::INIT_ERROR, 1, "Could not initialise glew.");
        }

        //Loading shaders according to conf file in resources/shaders
        //_shaders = ShaderManager(appPath);
        std::cout << appPath << std::endl;
        //for now, we use only one set of shaders:


        //init Imgui ? Nope, gets done befor by Controller.
        _widget = Widgets(/*_manager.get()->getWindowPtr(), _manager.get()->getGlContext()*/);

        //FOR 3d
        glEnable(GL_DEPTH_TEST);

        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLEW Version:   " << glewGetString(GLEW_VERSION) << std::endl;

    }
}
