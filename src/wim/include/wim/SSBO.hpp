//
// Created by piptouque on 01/01/2020.
//

#ifndef WORLD_IMAKER_SSBO_HPP
#define WORLD_IMAKER_SSBO_HPP

#pragma once

#include "Types.hpp"
#include "Exception.hpp"
#include "CommonDisplay.hpp"

namespace wim
{
    struct SSBO
    {
    private:
        GLuint _id;
    public:
        SSBO(const GLsizeiptr size, const SizeInt max);
        ~SSBO() {glDeleteBuffers(1, &_id);}


        inline GLuint id() const {return _id;}

        void alloc(const GLsizeiptr size, const SizeInt max) const;
        void bind(const GLuint programme, const char* storageBufferName, const GLuint binding) const;
        void update(const GLvoid* data, const GLsizeiptr size, const SizeInt nbUpdate) const;

    private:
        void bindObject(const GLuint binding) const;
        void bindBlock(const GLuint programme, const char* storageBufferName, const GLuint binding) const;

    };
}

#endif //WORLD_IMAKER_SSBO_HPP
