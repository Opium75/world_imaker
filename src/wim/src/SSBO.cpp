//
// Created by piptouque on 01/01/2020.
//

#include "../include/wim/SSBO.hpp"

#include <wim/FBO.hpp>
namespace wim
{

    SSBO::SSBO(const GLsizeiptr size, const SizeInt max) : _id()
    {
        glGenBuffers(1, &_id);
        this->alloc(size, max);
    }

    void SSBO::alloc(const GLsizeiptr size, const SizeInt max) const
    {
        //We have to allocate enough memory
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _id);
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
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, _id);
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
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, _id);
        bufferPtr = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
        std::memcpy(bufferPtr,
                    data,
                    size*nbUpdate);
        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

}