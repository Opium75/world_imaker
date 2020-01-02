//
// Created by piptouque on 25/11/2019.
//

//Already includes Cube, CubeStack, CubeWorld headers.
#include "../include/wim/Displayer.hpp"


namespace wim {

    Displayer::Displayer(const char* appPath, ModelPtr& model) :
            _windows(std::make_unique<glimac::SDLWindowManager>(DEFAULT_DISP_WINDOW_WIDTH, DEFAULT_DISP_WINDOW_HEIGHT, DISP_WINDOW_NAME)),
            _widgets(std::make_unique<WidgetManager>()),
            _renderer(std::make_unique<SceneRenderer>(appPath, model, _windows))
    {

    }

    void Displayer::display(const Cube &cube, const XUint x, const YUint y, const ZUint z) const
    {
        this->addToRenderingStacks( cube, Anchor(x,y,z) );
    }

    void Displayer::display(const CubeFloor &cubeFloor, const XUint x, const ZUint z) const
    {
        const YUint y = cubeFloor.floor();
        this->display(cubeFloor.cube(), x,y,z);
    }

    void Displayer::display(const CubeStack &cubeStack, const XUint x, const ZUint z) const
    {
        for( auto& cubeFloor : cubeStack.stack() )
        {
            this->display(cubeFloor, x, z);
        }
    }

    void Displayer::display(const CubeWorld &world) const
    {
        //setting-up anchors for (x,y)
        const XUint width = world.getWidth();
        const ZUint length = world.getLength();
        for(XUint x=0; x<width; ++x)
        {
            for(ZUint z=0; z<length; ++z)
            {
                this->display(world(x,z), x, z);
            }
        }
    }

    void Displayer::display(const Cursor& cursor) const
    {
        this->addToRenderingStacks(cursor, cursor.getPosition());
    }

    void Displayer::displayWidgets() const
    {
        ImGui::Begin("T'as vu ?");
        ImGui::End();
        /* */;
    }


    void Displayer::displayModel(const Model& model) const
    {
       this->display(*model.world());
       this->display(*model.cursor());
    }

    void Displayer::displayAll(const Model& model) const
    {
        /* Preparing IMGUI for new Frame */
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(this->windowManager()->window().get());
        ImGui::NewFrame();

        /*Adding elements to rendering stack. */
       // this->displayWidgets();
        this->displayModel(model);

        /* Rendering World */
        _renderer->render();
        /* Rendering IMGUI */
        ImGui::Render();
        glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    bool Displayer::readCubeIndex(Anchor& position, const GLint vX, const GLint vY) const
    {
        return _renderer->readCubeIndex(position, vX, vY);
    }
}
