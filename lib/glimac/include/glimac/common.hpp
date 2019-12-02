#pragma once

#include <GL/glew.h>
#include<memory>
#include "glm.hpp"

namespace glimac {
    typedef GLfloat ShapeFloat;
    typedef glm::vec3 ShapeVec3;
    typedef glm::vec2 ShapeVec2;

    struct ShapeVertex {
    public:
        ShapeVec3 _position;
        ShapeVec3 _normal;
        ShapeVec2 _texCoords;
    public:
        ShapeVertex() = default;
        ShapeVertex(const ShapeVec3&  pos, const ShapeVec3& normal) :
                _position(pos), _normal(normal) {}
        ShapeVertex(const ShapeVec3&  pos, const ShapeVec3& normal, const ShapeVec2& texCoords) :
            _position(pos), _normal(normal), _texCoords(texCoords) {}
        ~ShapeVertex() = default;

        inline const ShapeVec3& getPosition() {return _position;}
        inline const ShapeVec3& getNormal() {return _normal;}
        inline const ShapeVec2& getTexCoords() {return _texCoords;}

        inline void setPosition(const ShapeFloat x, const ShapeFloat y, const ShapeFloat z)
        {
            _position.x = x;
            _position.y = y;
            _position.z = z;
        }

        inline void setPosition(const ShapeVec3& position) {_position = position; }


        inline void setNormal(const ShapeFloat x, const ShapeFloat y, const ShapeFloat z)
        {
            _normal.x = x;
            _normal.y = y;
            _normal.z = z;
        }


        inline void normaliseNormal()
        {
            /* genius name */
            _normal = glm::normalize(_normal);
        }
        inline void setTexCoords(const ShapeFloat x, const ShapeFloat y)
        {
            _texCoords.x = x;
            _texCoords.y = y;
        }
    };
}
