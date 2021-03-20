#ifndef BOLA_HPP_
#define BOLA_HPP_

#include "abcg.hpp"
#include "entrada.hpp"

#include <list>
#include <random>

class OpenGLWindow;

class Bola {
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

  std::default_random_engine m_randomEngine;
  std::uniform_real_distribution<float> m_randomDist{-1.0f, 1.0f};

  glm::vec4 m_color{0.3};
  float m_rotation{};
  float m_scale{0.125f};
  glm::vec2 m_translation{glm::vec2(0)};
  glm::vec2 m_velocity{glm::vec2(0)};

};

#endif