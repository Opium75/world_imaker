//
// Created by piptouque on 20/12/2019.
//

#ifndef WORLD_IMAKER_SCENERENDERER_HPP
#define WORLD_IMAKER_SCENERENDERER_HPP

#pragma once

#include <memory>
#include <stack>
#include <deque>

#include "Displayable.hpp"
#include "Model.hpp"
#include "Listener.hpp"

#include "PatternManager.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"
#include "BufferManager.hpp"


namespace wim
{
    /*This class should be given the objects to be displayed
     * At every display iteration.
     * It can then optimise calls to shaders.
     */
    /* It is subscibed to Light Manager
     * so that is can send lights to shaders
     * only when there is a change
     */
    class SceneRenderer //: protected Listener
    {
    public:
        typedef std::stack<Renderable> RenderingStack;
        typedef std::vector<RenderingStack> ListRenderingStack;
    private:
        ModelPtr _model;
        PatternManagerPtr _patterns;
        ShaderManagerPtr _shaders;
        TextureManagerPtr _textures;
        BufferManagerPtr _buffers;
        ListRenderingStack _stacks; //one stack for each programme
    public:
        SceneRenderer(const char* appPath, ModelPtr& model, const WindowManagerPtr& windows);
        ~SceneRenderer();

        void useProgramme(const SizeInt index) const;

        void bindShaders() const;


        void addToStacks(const Renderable& item);

        const LightManagerPtr& lightManager() const;
        const CameraManagerPtr& cameraManager() const;

        UniformMatrix getCameraViewMatrix() const;

        bool readCubeIndex(Anchor& position, const GLint vX, const GLint vY) const;

        ///brief: render Displayable elements in stack, with respect to active Camera, lighting, and Shaders
        void render();
    private:
        SizeInt getStackIndex(const Renderable& item) const;
        void addToStack(const SizeInt index, const Renderable& item);
        void renderStack(RenderingStack& stack, const UniformMatrix& ProjMatrix);

        void renderFirstPass();
        void renderSecondPass();

        UniformMatrix getElementModelViewMatrix(const Renderable& item);
        UniformMatrix getProjectionMatrix() const;


        void updateMaterial(const Renderable& item);
        void updateMVPNMatrices(const UniformMatrix& MVMatrix, const UniformMatrix& ProjMatrix );
        void updateLights(const UniformMatrix& View) const;
        void updateFramebuffer() const;
        void updateCubeIndex(const Renderable& item) const;



        void drawItem(const Renderable& item) const;
        void drawFramebuffer() const;


        void toggleSceneToFramebuffer() const;
        void toggleFramebufferToScreen() const;
    };

}

#endif //WORLD_IMAKER_SCENERENDERER_HPP
