//
// Created by piptouque on 01/01/2020.
//

#ifndef WORLD_IMAKER_FBO_HPP
#define WORLD_IMAKER_FBO_HPP

#pragma once


#include "Types.hpp"
#include "Exception.hpp"
#include "CommonDisplay.hpp"

#include "ITO.hpp"
#include "Uniform.hpp"


namespace wim {

    static constexpr const GLenum DEFAULT_DRAWBUFFERS[] = {
            GL_COLOR_ATTACHMENT0, //texture of the whole scene to be rendered
            GL_COLOR_ATTACHMENT1 //texture with cube indices as colour
    };
    static constexpr const SizeInt NB_DEFAULT_DRAWBUFFERS = 2;

    ///brief; A class for Frame Buffer Objects
    class FBO {
    private:
        GLuint _id;
        GLuint _renderBuffer;
        ListITO _textures;
        Uniform _renderUniform;
        GLint _vWidth, _vHeight;
        WindowPtr _viewport;
    public:
        FBO(const WindowPtr &window, const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer);
        ~FBO();


        inline GLuint id() const {return _id;}

        const ITO& viewportTexture() const;
        const ITO& indicesTexture() const;

        Uniform& renderUniform();

        void update();

        ///Brief: render the displayed scene to attached framebuffer.
        void renderSceneToFramebuffer() const;

        void renderFramebufferToScreen() const;

        ///brief: Attemps to get the cube displayed at (x,y) in viewport. Returns true if successful, false otherwise.
        bool readCubeIndex(Point3Uint & position, const GLint vX, const GLint vY) const;

    private:
        void init(const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer);

        void alloc(const GLint vWidth, const GLint vHeight);
        void allocTextures(const GLint vWidth, const GLint vHeight);
        void allocRenderBuffer(const GLint vWidth, const GLint vHeight) const;

        void setDrawBufferList(const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer) const;

        void updateViewportSize();

        void getViewportSize(GLint &vWidth, GLint &vHeight);
    };

    void debug();
}

#endif //WORLD_IMAKER_FBO_HPP
