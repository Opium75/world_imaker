//
// Created by piptouque on 29/12/2019.
//

#include "../include/wim/BufferObject.hpp"

namespace wim
{
    void UBO::bindObject(const GLuint binding) const
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, _ubo);
    }

    void UBO::bindBlock(const GLuint programme, const char* uniBufferName, const GLuint binding) const
    {
        GLuint index = glGetUniformBlockIndex(programme, uniBufferName);
        if( index == GL_INVALID_INDEX)
        {
            throw Exception(ExceptCode::ILLIGAL, 1,
                            std::string("In programme #") + std::to_string(programme)+
                            std::string(" Required block not found: ") + uniBufferName);
        }
        glUniformBlockBinding(programme, index, binding);
    }


    void UBO::bind(const GLuint programme, const char* uniBufferName, const GLuint binding) const
    {
        this->bindBlock(programme, uniBufferName, binding);
        this->bindObject(binding);
    }

    void UBO::alloc(const GLsizeiptr size) const
    {
        glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
        glBufferData(GL_UNIFORM_BUFFER,
                     size,
                     nullptr,
                     GL_DYNAMIC_DRAW
        );
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UBO::update(const GLvoid* data, const GLsizeiptr size) const
    {
        /* Update everything in the structure */
        glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
        GLvoid *p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
        std::memcpy(p, data, size);
        glUnmapBuffer(GL_UNIFORM_BUFFER);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void SSBO::alloc(const GLsizeiptr size, const SizeInt max) const
    {
        //We have to allocate enough memory
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
        glBufferData(GL_SHADER_STORAGE_BUFFER,
                     size*max,
                     nullptr,
                     GL_DYNAMIC_COPY
        );
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void SSBO::bind(const GLuint programme, const char* storageBufferName, const GLuint binding) const
    {
        this->bindBlock(programme, storageBufferName, binding);
        this->bindObject(binding);
    }

    void SSBO::bindObject(const GLuint binding) const
    {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, _ssbo);
    }

    void SSBO::bindBlock(const GLuint programme, const char* storageBufferName, const GLuint binding) const
    {
        GLuint index = glGetProgramResourceIndex(programme, GL_SHADER_STORAGE_BLOCK, storageBufferName);
        if( index == GL_INVALID_INDEX )
        {
            throw Exception(ExceptCode::ILLIGAL, 1,
                            std::string("In programme #") + std::to_string(programme)+
                            std::string(" Required block not found: ") + storageBufferName);
        }
        glShaderStorageBlockBinding(programme, index, binding);
    }

    void SSBO::update(const GLvoid* data, const GLsizeiptr size, const SizeInt nbUpdate ) const
    {
        GLvoid *bufferPtr;
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _ssbo);
        bufferPtr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
        std::memcpy(bufferPtr,
                    data,
                    size*nbUpdate);
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    void ITO::setParametersCubeMaps() const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _ito);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //that minecraft look
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void ITO::setParameters2D() const
    {
        glBindTexture(GL_TEXTURE_2D, _ito);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void ITO::loadFace(const SizeInt indexFace, GLvoid *data, const GLsizei width, const GLsizei height) const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _ito);
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X+indexFace,
                0, //level of detail with regards to mipmap
                GL_RGBA,
                width,
                height,
                0, //border: alvays 0
                GL_RGBA,
                GL_FLOAT,
                data
        );
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        //
        this->setParametersCubeMaps();
        //glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    }

    void Uniform::localise(const GLuint programme, const char *uniAttrName)
    {
        _uId = glGetUniformLocation(programme, uniAttrName);
        /* if( _uId == -1)
         {
            throw Exception(ExceptCode::ILLIGAL, 1,
                             std::string("In programme #") + std::to_string(programme) +
                             std::string(" Required uniform not found: ") + uniAttrName);
         }*/
    }

    void Uniform::update(const GLint texId) const
    {
        glUniform1i(_uId, texId);
    }


    void IFO::allocTexture(const GLint vWidth, const GLint vHeight)
    {
       glBindTexture(GL_TEXTURE_2D, _renderTexture._ito);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGB,
                vWidth,
                vHeight,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                nullptr
        );
       glBindTexture(GL_TEXTURE_2D, 0);
       _vWidth = vWidth;
       _vHeight = vHeight;
    }

    void IFO::setParameters() const
    {
        glBindTexture(GL_TEXTURE_2D, ito());
            _renderTexture.setParameters2D();
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void IFO::allocDepthBuffer(const GLint vWidth, const GLint vHeight) const
    {

        glBindTexture(GL_TEXTURE_2D, ito());
            glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
                 glRenderbufferStorage(
                     GL_RENDERBUFFER,
                     GL_DEPTH_COMPONENT,
                     vWidth,
                     vHeight
                 );
                glFramebufferRenderbuffer(
                        GL_FRAMEBUFFER,
                        GL_DEPTH_ATTACHMENT,
                        GL_RENDERBUFFER,
                        _renderBuffer
                );
            //configuration
                glFramebufferTexture(
                        GL_FRAMEBUFFER,
                        GL_COLOR_ATTACHMENT0,
                        ito(),
                        0 //level
                );
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void IFO::alloc(const GLint vWidth, const GLint vHeight)
    {
        this->allocTexture(vWidth, vHeight);
        this->allocDepthBuffer(vWidth, vHeight);
    }

    void IFO::setDrawBufferList(const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer) const
    {

        glBindTexture(GL_TEXTURE_2D, ito());
            glBindRenderbuffer(GL_RENDERBUFFER, _renderBuffer);
                glDrawBuffers(nbDrawBuffers, listDrawBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void IFO::init(const SizeInt nbDrawBuffers, const GLenum *listDrawBuffer)
    {
        this->alloc(_vWidth, _vHeight);
        this->setParameters();
        this->setDrawBufferList(nbDrawBuffers, listDrawBuffer);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            throw Exception(ExceptCode::INIT_ERROR, 1, "Could not initialise IFO.");
        }
    }

    void IFO::update()
    {
        //checking if there is a change in Viewport dimensions
        GLint vWidth, vHeight;
        this->getViewportSize(vWidth,vHeight);
        if( vWidth != _vWidth || vHeight != _vHeight)
        {
            _vWidth = vWidth;
            _vHeight = vHeight;
            this->alloc(_vWidth, _vHeight);
        }
    }
}