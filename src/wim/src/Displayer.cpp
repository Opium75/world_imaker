//
// Created by piptouque on 25/11/2019.
//

//Already includes Cube, CubeStack, CubeWorld headers.
#include "../include/wim/Displayer.hpp"


namespace wim {



    void Displayer::display(const Cube &cube, const XUint x, const YUint y, const ZUint z) const
    {
       //todo: Add cube to rendering stack

        this->addToRenderingStack( cube, Renderable::Anchor(x,y,z) );
    }

    void Displayer::display(const CubeFloor &cubeFloor, const XUint x, const YUint y) const
    {
        const ZUint z = cubeFloor.floor();
        this->display(cubeFloor.cube(), x,y,z);
    }

    void Displayer::display(const CubeStack &cubeStack, const XUint x, const YUint y) const
    {
        for( auto& cubeFloor : cubeStack.stack() )
        {
            this->display(cubeFloor, x, y);
        }
    }

    void Displayer::display(const CubeWorld &world) const
    {
        //setting-up anchors for (x,y)
        const XUint width = world.getWidth();
        const YUint length = world.getLength();
        //Eigen matrices are column-major by default
        for(YUint y=0; y<length; ++y)
        {
            for(XUint x=0; x<width; ++x)
            {
                this->display(world(x,y), x, y);
            }
        }
    }

    void Displayer::displayWidgets() const
    {
        ImGui::Begin("T'as vu ?");
        ImGui::End();
        /* */;

        _widgets->showDemo(/*_manager->getWindowPtr(), _manager->getGlContext()*/);
    }


    void Displayer::displayModel(const Model& model) const
    {
       this->display(*model.getWorldPtr());
    }


    void Displayer::displayAll(const Model& model) const
    {
        /* Preparing IMGUI for new Frame */
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(this->getWindowPtr().get());
        ImGui::NewFrame();

        /* Actual displaying */
        this->displayWidgets();
        this->displayModel(model);

        /* Rendering IMGUI */
        ImGui::Render();
        glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
