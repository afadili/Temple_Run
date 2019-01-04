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
  float m_fDistance; /*!< position of the center of the camera */
  float m_fAngleX; /*!< Angle around the X-axis of the camera */
  float m_fAngleY; /*!< Angle around the Y-axis of the camera */
  float m_fPhi; /*!< Angle around the Y-axis of the camera */
  float m_fTheta; /*!< Angle around the Y-axis of the camera */
  glm::vec3 m_frontVector; /*!< Vector F */
  glm::vec3 m_leftVector; /*!< Vector L */
  glm::vec3 m_upVector; /*!< Vector U */
  bool m_isFPS = false; /*!< if the camera is in fps mode */

public:
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
   * \brief method to move the camera with the character's view
   */
  void moveUp();

  /**
   * \brief method to move the camera with the character's view
   */
  void moveForward(const float &x);

  /**
   * \brief method to move the camera with the character's view
   */
  void moveLeft(const float &x);

  /**
   * \brief method to move the camera with the character's view
   */
  void moveRight(const float &y);

  /**
   * \brief method that update the position of the camera
   */
  void Update() {
  }

  /**
   * \brief setter that reads the event and will set the camera depending on the event
   */
  void readEvent(const SDL_Event &e);

  /**
   * \brief getter of the camera's viewMatrix
   */
  glm::mat4 getViewMatrix() const;

};

#endif