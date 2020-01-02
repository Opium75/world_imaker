//
// Created by piptouque on 01/01/2020.
//

#ifndef WORLD_IMAKER_ITO_HPP
#define WORLD_IMAKER_ITO_HPP

#pragma once

#include <vector>
#include <memory>

#include "Types.hpp"
#include "Exception.hpp"
#include "CommonDisplay.hpp"

namespace wim
{

    ///BRIEF: A class of Texture objects using 2D TEXTURES and CUBEMAPS
    class ITO
    {
    private:
        GLuint _id;

    public:
        ITO(){glGenTextures(1, &_id);}
        ~ITO(){glDeleteTextures(1, &_id);}

        inline GLuint id() const {return _id;}

        void loadFace(const SizeInt indexFace, GLvoid *data, const GLsizei width, const GLsizei height) const;

        void setParameters2D() const;
        void setParametersCubeMaps() const;

        void allocFramebufferViewport(const GLsizei width, const GLsizei height) const;
        void allocFramebufferIndices(const GLsizei width, const GLsizei height) const;
    };

    typedef std::vector<ITO> ListITO;
    typedef std::shared_ptr<ListITO> ListITOPtr;
}
#endif //WORLD_IMAKER_ITO_HPP
