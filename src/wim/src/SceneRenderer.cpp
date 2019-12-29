//
// Created by piptouque on 22/12/2019.
//

#include "../include/wim/SceneRenderer.hpp"

namespace wim
{

    SceneRenderer::SceneRenderer(const char* appPath, ModelPtr& model, const WindowManagerPtr& windows):
            _model(model),
            _shaders(appPath, windows), _patterns(),
            _stacks(_shaders.getNumberProgrammes())
    {
       // this->subscribe(this->lightManager().get());
    }

    SceneRenderer::~SceneRenderer()
    {
     //   this->unsubscribe(this->lightManager().get());
    }

    void SceneRenderer::render()
    {
        //First, we can get the active camera.
        UniformMatrix ViewMatrix = this->getCameraViewMatrix();
        UniformMatrix ProjMatrix = this->getProjectionMatrix();

        this->updateLights(ViewMatrix);
        SizeInt programmeIndex=0;
        for( auto& stack : _stacks)
        {
            if( programmeIndex == _stacks.size()-1 )
            {
                /* last programme, -> foreground
                 * Ignoring depth -> clearing depth buffer
                 */
                glClear(GL_DEPTH_BUFFER_BIT);
            }
            _shaders.setCurrentProgramme(programmeIndex++);
            this->renderStack(stack, ProjMatrix);
        }
    }

    void SceneRenderer::renderStack(RenderingStack& stack, const UniformMatrix& ProjMatrix)
    {
        //Finally, we compute the MVPN matrices for each element before sending it.
        while( !stack.empty() )
        {
            //getting newt element
            Renderable item = stack.top();
            stack.pop();
            /* */

           //Computing Model
           UniformMatrix MVMatrix = this->getElementModelViewMatrix(item);

           //Sending Material and Matrices.
            this->updateMaterial(item);
            this->updateMVPNMatrices(MVMatrix, ProjMatrix );

            //Actual drawing of the element.
            this->drawItem(item);
        }
    }

    void SceneRenderer::updateLights(const UniformMatrix& View) const
    {
        _shaders.updateLights(*_model->lightManager(), View);
    }

    SizeInt SceneRenderer::getStackIndex(const Renderable& item) const
    {
        if( item.isTextured() )
        {
            return 1;
        }
        //Last stack used for forground rendering;
        else if( item.isInForeground() )
        {
            return _stacks.size()-1;
        }
        else //coloured
        {
            return 0;
        }
    }

    void SceneRenderer::addToStacks(const Renderable& item)
    {
        SizeInt index = this->getStackIndex(item);
        _stacks.at(index).push(item);
    }

    void SceneRenderer::addToStack(const SizeInt index, const Renderable& item)
    {
        _stacks.at(index).push(item);
    }

}