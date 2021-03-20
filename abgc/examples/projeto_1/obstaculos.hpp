#ifndef OBSTACULOS_HPP_
#define OBSTACULOS_HPP_

#include "abcg.hpp"
#include "entrada.hpp"

#include <list>
#include <random>

class OpenGLWindow;

class Obstaculos {
 public:
  void initializeGL(GLuint program);
  void paintGL(const Entrada &entrada);
  void terminateGL();
  
  void update(const Entrada &entrada, float deltaTime);
  void setRotation(float rotation) { m_rotation = rotation; }

 private:
  friend OpenGLWindow;

  GLuint m_program{};
  GLint m_translationLoc{};
  GLint m_colorLoc{};
  GLint m_scaleLoc{};
  GLint m_rotationLoc{};

  GLuint m_vao{};
  GLuint m_vbo{};
  GLuint m_ebo{};
  GLuint m_vboCores{};

  glm::vec4 m_color{0.3};
  float m_velocidadeAngular{0.0f};
  float m_rotation{};
  float m_scale{0.5f};
  glm::vec2 m_translation{glm::vec2(0)};
  glm::vec2 m_velocity{glm::vec2(0)};

};

#endif