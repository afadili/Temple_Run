#include <cmath>
#include <glm/glm.hpp>

namespace glimac {

  class FreeflyCamera {
  private:
    glm::vec3 _Position;
    float _fPhi;
    float _fTheta;
    glm::vec3 _FrontVector;
    glm::vec3 _LeftVector;
    glm::vec3 _UpVector;
  public:

    void computeDirectionVectors() {
      _FrontVector = glm::vec3(cos(_fTheta) * sin(_fPhi), sin(_fTheta), cos(_fTheta) * cos(_fPhi));
      _LeftVector = glm::vec3(sin(_fPhi + M_PI / 2), 0, cos(_fPhi + M_PI / 2));
      _UpVector = glm::cross(_FrontVector, _LeftVector);
    }

    FreeflyCamera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), float phi = M_PI, float theta = 0.0)
    : _Position(pos), _fPhi(phi), _fTheta(theta) {
      computeDirectionVectors();
    }

    void moveLeft(float t) {
      _Position += t*_LeftVector;
    }

    void moveFront(float t) {
      _Position += t*_FrontVector;
    }

    void rotateLeft(float degrees) {
      _fPhi += glm::radians(degrees);
      computeDirectionVectors();
    }

    void rotateUp(float degrees) {
      _fTheta += glm::radians(degrees);
      computeDirectionVectors();
    }

    glm::mat4 getViewMatrix() const {
      return glm::lookAt(_Position, _Position + _FrontVector, _UpVector);
    }

  };
}