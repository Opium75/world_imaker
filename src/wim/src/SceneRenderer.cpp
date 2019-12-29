//
// Created by piptouque on 22/12/2019.
//

#include "../include/wim/SceneRenderer.hpp"

namespace wim
{

    SceneRenderer::SceneRenderer(const char* appPath, ModelPtr& model):
            _model(model),
            _shaders(appPath), _patterns(),_stack()
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
        UniformMatrix ViewMatrix = this->getProjectionMatrix();
        UniformMatrix ProjMatrix = this->getProjectionMatrix();

        /** IMPORTANT : light sources are not updated here
         ** only when there is a change in Light Manager
         ** through a Listerner
         **/
        // _shaders.bindShaders();
         this->updateLights(ViewMatrix);
        //Finally, we compute the MVPN matrices for each element before sending it.
        while( !_stack.empty() )
        {
            //getting newt element
            Renderable item = _stack.top();
            _stack.pop();
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
}