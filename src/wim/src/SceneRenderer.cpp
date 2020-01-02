//
// Created by piptouque on 22/12/2019.
//

#include "../include/wim/SceneRenderer.hpp"

namespace wim
{

    SceneRenderer::SceneRenderer(const char* appPath, ModelPtr& model, const WindowManagerPtr& windows):
            _model(model),
            _patterns(std::make_unique<PatternManager>()),
            _shaders(std::make_unique<ShaderManager>(appPath)),
            _textures(std::make_unique<TextureManager>(appPath)),
            _buffers(std::make_unique<BufferManager>(_textures, windows)),
            _stacks(_shaders->getNumberProgrammes()-1)
    {
       // this->subscribe(this->lightManager().get())
        this->bindShaders();
        _buffers->loadCubeMaps(_textures->getCubeMaps());
         Displayable::linkTextures(_buffers->getListITO());
    }

    SceneRenderer::~SceneRenderer()
    {
     //   this->unsubscribe(this->lightManager().get());
    }

    void SceneRenderer::render()
    {
        this->updateFramebuffer();
        this->toggleSceneToFramebuffer();
           this->renderFirstPass();
        this->toggleFramebufferToScreen();
            this->renderSecondPass();
    }

    void SceneRenderer::renderSecondPass()
    {
        //last programme used  to render the single squad.
        this->useProgramme(_shaders->getNumberProgrammes() - 1);
        this->drawFramebuffer();
    }
    void SceneRenderer::renderFirstPass()
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
            this->useProgramme(programmeIndex++);
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
            this->updateMVPNMatrices(MVMatrix, ProjMatrix);

            //Sending the position of the item for selection through framebuffer
            this->updateCubeIndex(item);

            //Actual drawing of the element.
            this->drawItem(item);
        }
    }

    void SceneRenderer::updateLights(const UniformMatrix& View) const
    {
        _buffers->updateLights(*_model->lightManager(), View);
    }

    void SceneRenderer::updateCubeIndex(const Renderable& item) const
    {
        _buffers->updateCubeIndex(item.getAnchor());
    }

    void SceneRenderer::useProgramme(const SizeInt index) const
    {
        _shaders->useProgramme(index);
        _buffers->localiseUniform(_shaders->currentSender());
    }

    SizeInt SceneRenderer::getStackIndex(const Renderable& item) const
    {
        if( item.isTextured() )
        {
            return 1;
        }
        //Last stack used for foreground rendering;
        else if( item.isInForeground() )
        {
            return _stacks.size()-1;
        }
        else //coloured
        {
            return 0;
        }
    }

    void SceneRenderer::bindShaders() const
    {
        _buffers->bindShaders(_shaders);
    }

    void SceneRenderer::addToStacks(const Renderable& item)
    {
        SizeInt index = this->getStackIndex(item);
        this->addToStack(index, item);
    }

    void SceneRenderer::addToStack(const SizeInt index, const Renderable& item)
    {
        _stacks.at(index).push(item);
    }

    void SceneRenderer::toggleSceneToFramebuffer() const
    {
        _buffers->renderSceneToFramebuffer();
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void SceneRenderer::toggleFramebufferToScreen() const
    {
        _buffers->renderFramebufferToScreen();
        glDisable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);
    }


    bool SceneRenderer::readCubeIndex(Anchor& position, const GLint vX, const GLint vY) const
    {
        return _buffers->readCubeIndex(position, vX, vY);
    }

    void SceneRenderer::drawItem(const Renderable& item) const
    {
        _patterns->draw(item);
    }
    void SceneRenderer::drawFramebuffer() const
    {
        _patterns->drawFramebuffer(_buffers->getFramebuffer());
    }

    inline UniformMatrix SceneRenderer::getElementModelViewMatrix(const Renderable& item){return this->cameraManager()->getElementModelViewMatrix(item);}
    inline UniformMatrix SceneRenderer::getProjectionMatrix() const{return this->cameraManager()->getProjectionMatrix();}


    inline void SceneRenderer::updateMaterial(const Renderable& item){return _buffers->updateMaterial(item.getMaterial(), item.isTextured());}
    inline void SceneRenderer::updateMVPNMatrices(const UniformMatrix& MVMatrix, const UniformMatrix& ProjMatrix ){return _buffers->updateMatrices(MVMatrix, ProjMatrix);}

    inline void SceneRenderer::updateFramebuffer() const {_buffers->updateFramebuffer();}

    inline const LightManagerPtr& SceneRenderer::lightManager() const {return _model->lightManager();}
    inline const CameraManagerPtr& SceneRenderer::cameraManager() const {return _model->cameraManager();}

    inline UniformMatrix SceneRenderer::getCameraViewMatrix() const {return this->cameraManager()->getCameraViewMatrix();}


}