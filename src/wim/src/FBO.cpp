//
// Created by piptouque on 01/01/2020.
//

#include "wim/FBO.hpp"

namespace wim {

    FBO::FBO(const WindowPtr &window, const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer) :
            _textures(NB_DEFAULT_DRAWBUFFERS),
            _viewport(window)
    {
        glGenFramebuffers(1, &_id);
        glGenRenderbuffers(1, &_renderBuffer);
        //
        this->getViewportSize(_vWidth, _vHeight);
        this->init(nbDrawBuffers, listDrawBuffer);
    }

    FBO::~FBO()
    {
        glDeleteRenderbuffers(1, &_renderBuffer);
        glDeleteFramebuffers(1, &_id);
    }


    const ITO& FBO::viewportTexture() const
    {
        return _textures.at(0);
    }

    const ITO& FBO::indicesTexture() const
    {
        return _textures.at(1);
    }

    Uniform& FBO::renderUniform()
    {
        return _renderUniform;
    }


    void FBO::allocTextures(const GLint vWidth, const GLint vHeight) {
        glBindFramebuffer(GL_FRAMEBUFFER, _id);
            _textures.at(0).allocFramebufferViewport(vWidth, vHeight);
            _textures.at(1).allocFramebufferIndices(vWidth, vHeight);
            //configuration
             glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT0,
                GL_TEXTURE_2D,
                this->viewportTexture().id(), //viewport
                0 //level
             );
             glFramebufferTexture2D(
                GL_FRAMEBUFFER,
                GL_COLOR_ATTACHMENT1,
                GL_TEXTURE_2D,
                this->indicesTexture().id(), // indices of cubes in viewport.
                0
             );
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }


    void FBO::allocRenderBuffer(const GLint vWidth, const GLint vHeight) const {
        glBindFramebuffer(GL_FRAMEBUFFER, _id);
            glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
                glRenderbufferStorage(
                     GL_RENDERBUFFER,
                     GL_DEPTH24_STENCIL8,
                     vWidth,
                     vHeight
                );
                glFramebufferRenderbuffer(
                        GL_FRAMEBUFFER,
                        GL_DEPTH_STENCIL_ATTACHMENT,
                        GL_RENDERBUFFER,
                        _renderBuffer
                );
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FBO::alloc(const GLint vWidth, const GLint vHeight)
    {
        this->allocTextures(vWidth, vHeight);
        this->allocRenderBuffer(vWidth, vHeight);
    }

    void FBO::setDrawBufferList(const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer) const
    {

       glBindFramebuffer(GL_FRAMEBUFFER, _id);
           glDrawBuffers(nbDrawBuffers, listDrawBuffer);
       glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FBO::init(const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer)
    {

        this->alloc(_vWidth, _vHeight);
        this->setDrawBufferList(nbDrawBuffers, listDrawBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, _id);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            throw Exception(ExceptCode::INIT_ERROR, 1, "Could not initialise FBO.");
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    bool FBO::readCubeIndex(Anchor& position, const GLint vX, const GLint vY) const
    {
        GLuint data[4];
        glBindFramebuffer(GL_READ_FRAMEBUFFER,_id);
            glReadBuffer(GL_COLOR_ATTACHMENT1);
            glReadPixels(
                    vX,_vHeight-vY,
                    1,1,
                    GL_RGBA_INTEGER,
                    GL_UNSIGNED_INT,
                    data
            );
        glBindFramebuffer(GL_READ_FRAMEBUFFER,0);
        if( data[3] == 0)
        {
            //If the specified pixel was not part of a cube.
            return false;
        }
        position = Anchor(data[0], data[1], data[2]);
        return true;
    }


    void FBO::updateViewportSize() {
        //checking if there is a change in Viewport dimensions
        GLint vWidth, vHeight;
        this->getViewportSize(vWidth, vHeight);
        if (vWidth != _vWidth || vHeight != _vHeight) {
            _vWidth = vWidth;
            _vHeight = vHeight;
            this->alloc(_vWidth, _vHeight);
        }
    }

    void FBO::update() {
        this->updateViewportSize();
    }


    void FBO::renderSceneToFramebuffer() const {
        glBindFramebuffer(GL_FRAMEBUFFER, _id);

    }

    void FBO::renderFramebufferToScreen() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

    void FBO::getViewportSize(GLint &vWidth, GLint &vHeight)
    {
        SDL_GetWindowSize(_viewport.get(), &vWidth, &vHeight);
    }
}