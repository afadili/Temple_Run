/**
 * \file Camera.hpp
 * \brief Decalaration of the class "Camera"
 */

#ifndef __CAMERA__HPP
#define __CAMERA__HPP

#include <iostream>
#include <glimac/glm.hpp>
#include <vector>
#include <string>
#include <glimac/SDLWindowManager.hpp>

/**
 * \class Camera
 * \brief Camera management
 */
class Camera {
private:

  glm::vec3 m_center; /*!< position of the center of the camera */
  glm::vec3 m_eyesPosition; /*!< position of the "eyes" of the subject for the first person */

  float m_fDistance; /*!< distance from the center of the subject */
  float m_fAngleX; /*!< Angle around the X-axis of the camera in degrees */
  float m_fAngleY; /*!< Angle around the Y-axis of the camera in degrees */

  float m_fPhi; /*!< spherical coordinates of the the vector F */
  float m_fTheta; /*!< sperical coordinates of the vector F */
  glm::vec3 m_frontVector; /*!< Vector F */
  glm::vec3 m_leftVector; /*!< Vector L */
  glm::vec3 m_upVector; /*!< Vector U */

  unsigned int m_currentCamera; /*!< 1 = third person / 2 = first person / 3 = rotation */


public:
  static const float VIEW_WIDTH;

  /**
   * \brief constructor of Camera
   */
  Camera();

  /**
   * \brief destructor of Camera
   */
  ~Camera() {
  }
  /**
   * \brief Initialize the camera information
   * \param distance : distance from the center of the subject
   * \param angleY : angle around the Y-axis of the camera in radian 
   * \param eyesPosition : position of the "eyes" of the subject for the first person
   */
  void initialization(const float &distance, const float &angleY = 0.f, const glm::vec3 &eyesPosition = glm::vec3());

  /**
   * \brief modification of the camera depending on the events
   * \param e : SDL event
   */
  void eventManager(const SDL_Event &e);

  /**
   * \brief update the position of the camera
   */
  void update(const glm::vec3 &center);

  /**
   * \brief Getter of distance
   * \return m_fDistance
   */
  inline
  const float &distance() const {
    return m_fDistance;
  }

  /**
   * \brief Setter of distance
   * \return m_fDistance
   */
  inline
  float &distance() {
    return m_fDistance;
  }

  /**
   * \brief 
   * \param rotationY in radian
   */
  void rotate(const float &rotationY);

  /**
   * \brief get view matrix
   */
  glm::mat4 getViewMatrix() const;

private:

  /**
   * \brief to move forward in third person
   * \param delta
   */
  void moveForwardThirdPerson(const float &delta);

  /**
   * \brief to rotate left in third person
   * \param degrees
   */
  void rotateLeftThirdPerson(const float &degrees);

  /**
   * \brief to rotate right in third person
   * \param degrees
   */
  void rotateRightThirdPerson(const float &degrees);

  /**
   * \brief to move forward in first person
   * \param t
   */
  void moveForwardFirstPerson(const float &t);

  /**
   * \brief to move left in first person
   * \param t
   */
  void moveLeftFirstPerson(const float &t);

  /**
   * \brief to rotate in first person
   * \param t
   */
  void rotateFrontFirstPerson(const float &degrees);

  /**
   * \brief to rotate left in first person
   * \param degrees
   */
  void rotateLeftFirstPerson(const float &degrees);

  /**
   * \brief direction vector calculator
   */
  void computeDirectionVectors();

  template<typename T>
  T clamp(const T &n, const T &lower, const T &upper) {
    return std::max(lower, std::min(n, upper));
  }
};

#endif