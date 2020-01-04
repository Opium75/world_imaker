//
// Created by piptouque on 01/01/2020.
//

#ifndef WORLD_IMAKER_UNIFORM_HPP
#define WORLD_IMAKER_UNIFORM_HPP

#pragma once


#include "Types.hpp"
#include "Exception.hpp"
#include "CommonDisplay.hpp"

#include "Displayable.hpp"

namespace wim
{
    struct Uniform
    {
    private:
        GLint _id;
    public:
        Uniform()
        {
        }
        ~Uniform() = default;


        inline GLuint id() const {return _id;}

        void localise(const GLuint programme, const char* uniAttrName);
        void updateCubeIndex(const Point3Uint& anchor) const;

    };
    struct UBO
    {
    private:
        GLuint _id;
    public:
        UBO(const GLsizeiptr size) : _id()
        {
            glGenBuffers(1, &_id);
            this->alloc(size);

        }
        ~UBO() {glDeleteBuffers(1,&_id);}

        inline GLuint id() const {return _id;}

        void bind(const GLuint programme, const char* uniBufferName, const GLuint binding) const;
        void alloc(const GLsizeiptr size) const;
        void update(const GLvoid* data,  const GLsizeiptr size) const;
    private:
        void bindBlock(const GLuint programme, const char* uniBufferName, const GLuint binding) const;
        void bindObject(const GLuint binding) const;
    };
}

#endif //WORLD_IMAKER_UNIFORM_HPP
