#include "glimac/TrackballCamera.hpp"

namespace glimac {
    TrackballCamera::TrackballCamera(const GLfloat fDistance, const GLfloat fAngleX, const GLfloat fAngleY, const GLfloat zoomSpeed, const GLfloat xSpeed, const GLfloat ySpeed) :
            m_fDistance(fDistance), m_fAngleX(fAngleX), m_fAngleY(fAngleY),
            m_zoomSpeed(zoomSpeed),  m_xSpeed(xSpeed), m_ySpeed(ySpeed)
    {}

    void TrackballCamera::moveFront(const GLfloat delta) {
        m_fDistance += delta;
    }

    void TrackballCamera::rotateLeft(const GLfloat degrees) {
        m_fAngleY -= degrees;
    }

    void TrackballCamera::rotateUp(const GLfloat degrees) {
        m_fAngleX += degrees;
    }

    glm::mat4 TrackballCamera::getViewMatrix() const {
        glm::mat4 viewMatrix = glm::translate(
                glm::mat4(1.f),
                glm::vec3(0.f, 0.f, -m_fDistance)
        );

        viewMatrix *= glm::rotate(
                glm::mat4(1.f),
                glm::radians(m_fAngleX),
                glm::vec3(1.f, 0.f, 0.f)
        );

        viewMatrix *= glm::rotate(
                glm::mat4(1.f),
                glm::radians(m_fAngleY),
                glm::vec3(0.f, 1.f, 0.f)
        );

        return viewMatrix;
    }

    void TrackballCamera::zoomInput(const GLint input)
    {
        this->moveFront(input*m_zoomSpeed);
    }

    void TrackballCamera::rotate(const GLfloat phi, const GLfloat theta)
    {
        this->rotateLeft(theta*m_ySpeed);
        this->rotateUp(phi*m_xSpeed);
    }
}

