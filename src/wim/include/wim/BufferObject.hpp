//
// Created by piptouque on 29/12/2019.
//

#ifndef WORLD_IMAKER_BUFFEROBJECT_HPP
#define WORLD_IMAKER_BUFFEROBJECT_HPP

#pragma once

#include <glimac/SDLWindowManager.hpp>

#include "CommunDisplay.hpp"
#include "Types.hpp"
#include "Exception.hpp"

namespace wim
{

    typedef glimac::SDLWindowManager::SDL_WindowPtr WindowPtr;
    /*Names of uniform attributs as they are used in the shaders
  * For now, we will only support one light source. IN POINT LIGHT
  */
    //MATRICES
    static constexpr const char* UNI_BLOCK_MATRICES_NAME = "bMatrices";
    //MATERIAL
    static constexpr const char* UNI_BLOCK_MATERIAL_NAME = "bMaterial";
    //BASE TEXTURE
    static constexpr const char* UNI_LOC_BASETEXTURE_NAME = "uBaseTexture";
    /* LIGHTs
     * One ambiant, and multiple point and directional lights
     * (using shader storage buffers; see Light.hpp for storage details.)
     */
    static constexpr const char* UNI_BLOCK_AMBIANTLIGHT_NAME = "bAmbiantLight";

    static constexpr const char* STORAGE_BLOCK_POINTLIGHT_NAME = "sPointLight";
    static constexpr const char* STORAGE_BLOCK_DIRECTIONLIGHT_NAME = "sDirectionLight";
    static constexpr const char* STORAGE_BLOCK_LIGHTNUMBER_NAME = "sLightNumber";
    /* SEE STD140 FOR DETAILS ON OFFSETS AND SIZES
     * AS HANDLED BY GLSL
     */

    //UBOs
    static const GLuint BINDING_MATRICES_INDEX = 0;
    static const GLuint BINDING_MATERIAL_INDEX = 1;
    static const GLuint BINDING_AMBIANTLIGHT_INDEX = 2;

    //SSBOs
    static const GLuint BINDING_LIGHTNUMBER_INDEX = 0;
    static const GLuint BINDING_POINTLIGHT_INDEX = 1;
    static const GLuint BINDING_DIRECTIONLIGHT_INDEX = 2;



    struct Uniform
    {
    public:
        GLint _uId;
    public:
        Uniform()
        {
        }
        ~Uniform() = default;

        void localise(const GLuint programme, const char* uniAttrName);
        void update(const GLint texId ) const;

    };
    struct UBO
    {
    public:
        GLuint _ubo;
    public:
        UBO(const GLsizeiptr size) : _ubo()
        {
            glGenBuffers(1, &_ubo);
            this->alloc(size);

        }
        ~UBO() {glDeleteBuffers(1,&_ubo);}


        void bind(const GLuint programme, const char* uniBufferName, const GLuint binding) const;
        void alloc(const GLsizeiptr size) const;
        void update(const GLvoid* data,  const GLsizeiptr size) const;
    private:
        void bindBlock(const GLuint programme, const char* uniBufferName, const GLuint binding) const;
        void bindObject(const GLuint binding) const;
    };

    struct SSBO
    {
    public:
        GLuint _ssbo;
    public:
        SSBO(const GLsizeiptr size, const SizeInt max) : _ssbo()
        {
            glGenBuffers(1, &_ssbo);
            this->alloc(size, max);
        }
        ~SSBO() {glDeleteBuffers(1, &_ssbo);}

        void alloc(const GLsizeiptr size, const SizeInt max) const;
        void bind(const GLuint programme, const char* storageBufferName, const GLuint binding) const;
        void update(const GLvoid* data, const GLsizeiptr size, const SizeInt nbUpdate) const;

    private:
        void bindObject(const GLuint binding) const;
        void bindBlock(const GLuint programme, const char* storageBufferName, const GLuint binding) const;

    };

    ///BRIEF: A classof Texture objects using 2D TEXTURES and CUBEMAPS
    class ITO
    {
    public:
        GLuint _ito;
    public:
        ITO(){glGenTextures(1, &_ito);}
        ~ITO(){glDeleteTextures(1, &_ito);}

        void loadFace(const SizeInt indexFace, GLvoid *data, const GLsizei width, const GLsizei height) const;

        void setParameters2D() const;
        void setParametersCubeMaps() const;
    };

    static constexpr const GLenum DEFAULT_DRAWBUFFERS[] = {GL_COLOR_ATTACHMENT0};
    static constexpr const SizeInt NB_DEFAULT_DRAWBUFFERS = 1;

    ///brief; A class for Frame Buffer Objects
    class IFO
    {
    public:
        GLuint _ifo;
        GLuint _renderBuffer;
        ITO _renderTexture;
        GLint _vWidth, _vHeight;
        WindowPtr _viewport;
    public:
        IFO(const WindowPtr& window, const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer) :
            _viewport(window)
        {
            glGenFramebuffers(1, &_ifo);
            glGenRenderbuffers(1, &_renderBuffer);
            //
            this->getViewportSize(_vWidth, _vHeight);
            this->init(nbDrawBuffers, listDrawBuffer);
        }
        ~IFO()
        {
            glDeleteRenderbuffers(1, &_renderBuffer);
            glDeleteFramebuffers(1, &_ifo);
        }

        GLuint ito() const {return _renderTexture._ito;}

        void update();
    private:
        void init(const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer);
        void alloc(const GLint vWidth, const GLint vHeight);
        void allocTexture(const GLint vWidth, const GLint vHeight);
        void setParameters() const;
        void allocDepthBuffer(const GLint vWidth, const GLint vHeight) const;
        void setDrawBufferList(const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer) const;

        void getViewportSize(GLint &vWidth, GLint &vHeight)
        {
            SDL_GetWindowSize(_viewport.get(), &vWidth, &vHeight);
        }
    };

}
#endif //WORLD_IMAKER_BUFFEROBJECT_HPP
