//
// Created by piptouque on 01/01/2020.
//

#include "../include/wim/ITO.hpp"

namespace wim
{
    void ITO::setParametersCubeMaps() const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //that minecraft look
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void ITO::setParameters2D() const
    {
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void ITO::loadFace(const SizeInt indexFace, GLvoid *data, const GLsizei width, const GLsizei height) const
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
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

    void ITO::allocFramebufferViewport(const GLsizei width, const GLsizei height) const
    {
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexImage2D(
               GL_TEXTURE_2D,
                0, //level of detail with regards to mipmap
                GL_RGB,
                width,
                height,
                0, //border: always 0
                GL_RGB,
                GL_FLOAT,
                nullptr
        );
        glBindTexture(GL_TEXTURE_2D, 0);
        //
        this->setParameters2D();
    }

    void ITO::allocFramebufferIndices(const GLsizei width, const GLsizei height) const
    {
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexImage2D(
                GL_TEXTURE_2D,
                0, //level of detail with regards to mipmap
                GL_RGBA32UI,
                width,
                height,
                0, //border: always 0
                GL_RGBA_INTEGER,
                GL_UNSIGNED_INT,
                nullptr
        );
        glBindTexture(GL_TEXTURE_2D, 0);
        //
        this->setParameters2D();
    }
}