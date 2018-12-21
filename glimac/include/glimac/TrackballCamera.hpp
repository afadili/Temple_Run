namespace glimac {

  class TrackballCamera {
  private:
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;
  public:
    // Constructeur: 

    TrackballCamera() :
    m_fDistance(5.f), m_fAngleX(0.), m_fAngleY(0.) {
    }

    TrackballCamera(const float &distance, const float &angleX, const float &angleY) :
    m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY) {
    }

    // Avancer / reculer la caméra, delta > 0 avance, delta < 0 reculer

    inline
    void moveFront(const float &delta) {
      m_fDistance -= delta;
    }

    // Tourner latéralement autour du centre de vision

    inline
    void rotateLeft(const float &degrees) {
      m_fAngleY += degrees;
    }

    // Tourner verticalement autour du centre de vision

    inline
    void rotateUp(const float &degrees) {
      m_fAngleX += degrees;
    }

    // Calculer la ViewMatrix de la caméra

    glm::mat4 getViewMatrix() const {
      glm::mat4 viewMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f, m_fDistance));
      viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f));
      viewMatrix = glm::rotate(viewMatrix, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f));
      return viewMatrix;
    }

  };
}