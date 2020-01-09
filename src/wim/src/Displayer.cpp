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

    void Displayer::display(const Cube &cube) const
    {
        Anchor anchor = Anchor(cube.position());
        this->addToRenderingStacks( cube, anchor);

    }

    void Displayer::display(const CubeFloor &cubeFloor) const
    {
        this->display(cubeFloor.cube());
    }

    void Displayer::display(const CubeStack &cubeStack) const
    {
        for( auto& cubeFloor : cubeStack.stack() )
        {
            this->display(cubeFloor);
        }
        /* The base of each stack should be selectable by mouse,
         * So adding an invisible quad at the bottom.
         */
        this->addToRenderingStacks(cubeStack.base(), cubeStack.x(),cubeStack.z());
        this->addToRenderingStacks(cubeStack.hiddenBase(), cubeStack.x(),cubeStack.z());
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
                this->display(world(x,z));
            }
        }
    }

    void Displayer::display(const Cursor& cursor) const
    {
        this->addToRenderingStacks(cursor, cursor.getPosition());
        //Rendering as a selected element, which is a cursor
        for( const auto& selected : cursor.selection()->selected() )
        {
            if( !selected->isDeleted() )
            {
              //  std::cout << "Coucou " << selected->position() << std::endl;
                this->addToRenderingStacks(*selected, Anchor(selected->position()));
            }
        }
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

    bool Displayer::readCubeIndex(Point3Uint& position, const GLint vX, const GLint vY) const
    {
        return _renderer->readCubeIndex(position, vX, vY);
    }


    void Displayer::addToRenderingStacks(const Displayable &object, const Anchor &anchor, const FloatType rotX, const FloatType rotY) const
    {
        _renderer->addToStacks(Renderable(object, anchor, rotX, rotY));
    }


    void Displayer::addToRenderingStacks(const Quad &quad, const XUint x, const ZUint z) const
    {
        _renderer->addToStacks(quad.getRenderable(x,z));
    }


}
