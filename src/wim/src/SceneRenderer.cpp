//
// Created by piptouque on 22/12/2019.
//

#include "../include/wim/SceneRenderer.hpp"

namespace wim
{
    void SceneRenderer::render()
    {
        //First, we can get the active camera.
        UniformMatrix ProjMatrix = this->getProjectionMatrix();

        //todo: Then, send lighting from every source.
        this->updateLightsCurrent();

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
            this->updateMaterialCurrent(item.getMaterial());
            this->updateMVPNMatricesCurrent(MVMatrix, ProjMatrix);

            //Actual drawing of the element.
            this->drawPattern(item.getDisplayPattern());
        }
    }

    void SceneRenderer::updateLightsCurrent() const
    {
        //Ambiant light.
        _shaders.updateLightsCurrent(_model->getLightManagerPtr()->getAmbiantLight());
    }
}