#include <cmath>
#include <glm/glm.hpp>

namespace glimac {

    class FreeflyCamera {
    private:
        glm::vec3 m_position; // Position de la camera
        float m_fPhi; // Coord du vecteur sphérique F
        float m_fTheta; // Coord du vecteur sphérique F
        glm::vec3 m_frontVector; // Vecteur F
        glm::vec3 m_leftVector; // Vecteur L
        glm::vec3 m_upVector; // Vecteur U

        void computeDirectionVectors(){
            m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi),
                                     std::sin(m_fTheta),
                                     std::cos(m_fTheta) * std::cos(m_fPhi));
            
            m_leftVector = glm::vec3(std::sin(m_fPhi + M_PI/2),
                                    0,
                                    std::cos(m_fPhi + M_PI/2));
            
            m_upVector = glm::cross(m_frontVector,
                                   m_leftVector);
        }

    public:
        // Constructeur: 

        FreeflyCamera() : m_position(glm::vec3(0.f, 0.f, 0.f)), m_fPhi(M_PI), m_fTheta(0) {
            computeDirectionVectors();
        }

        void moveFront(const float &t){
            m_position += t * m_frontVector;
            m_upVector = glm::cross(m_frontVector,m_leftVector);
        }

        void moveLeft(const float &t){
            m_position += t * m_leftVector;
            m_upVector = glm::cross(m_frontVector,m_leftVector);
        }

        void rotateFront(const float &degrees){
            m_fPhi += glm::radians(degrees);
            m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi), std::sin(m_fTheta),  std::cos(m_fTheta) * std::cos(m_fPhi));
            m_leftVector = glm::vec3(std::sin(m_fPhi + M_PI/2), 0, std::cos(m_fPhi + M_PI/2));
        }

        void rotateLeft(const float &degrees){
            m_fTheta += glm::radians(degrees);
            m_frontVector = glm::vec3(std::cos(m_fTheta) * std::sin(m_fPhi), std::sin(m_fTheta),  std::cos(m_fTheta) * std::cos(m_fPhi));
            m_leftVector = glm::vec3(std::sin(m_fPhi + M_PI/2), 0, std::cos(m_fPhi + M_PI/2));
        }

        glm::mat4 getViewMatrix() const{
            return glm::lookAt(m_position, m_position + m_frontVector, m_upVector);
        }

        

    };
}