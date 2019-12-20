#include "glimac/FreeflyCamera.hpp"
namespace glimac {

    FreeflyCamera::FreeflyCamera(const glm::vec3 Position, const float fPhi, const float fTheta) :
            m_Position(Position), m_fPhi(fPhi), m_fTheta(fTheta) {
        this->computeDirectionVector();
    }

    void FreeflyCamera::moveLeft(const float t) {
        m_Position += m_LeftVector * t;
    }

    void FreeflyCamera::moveFront(const float t) {
        m_Position += m_FrontVector * t;
    }

    void FreeflyCamera::rotateLeft(const float degrees) {
        m_fPhi += glm::radians(degrees);
        this->computeDirectionVector();
    }

    void FreeflyCamera::rotateUp(const float degrees) {
        m_fTheta += glm::radians(degrees);
        this->computeDirectionVector();
    }

    void FreeflyCamera::computeDirectionVector(void) {
        float cosPhi, sinPhi, cosTheta, sinTheta;
        cosPhi = glm::cos(m_fPhi);
        sinPhi = glm::sin(m_fPhi);
        cosTheta = glm::cos(m_fTheta);
        sinTheta = glm::sin(m_fTheta);
        this->m_FrontVector = glm::vec3(
                cosTheta * sinPhi,
                sinTheta,
                cosTheta * cosPhi
        );
        this->m_LeftVector = glm::vec3(
                cosPhi,
                0,
                -sinPhi
        );
        this->m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
    }

    glm::mat4 FreeflyCamera::getViewMatrix(void) const {
        return glm::lookAt(
                m_Position,
                m_Position + m_FrontVector,
                m_UpVector
        );
    }

}