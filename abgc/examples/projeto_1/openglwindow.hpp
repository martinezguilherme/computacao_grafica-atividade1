#ifndef OPENGLWINDOW_HPP_
#define OPENGLWINDOW_HPP_

#include <imgui.h>

#include <random>

#include "abcg.hpp"
#include "entrada.hpp"
#include "bola.hpp"
#include "cenario.hpp"
#include "aviao.hpp"
#include "obstaculos.hpp"

class OpenGLWindow : public abcg::OpenGLWindow {
 protected:
  void handleEvent(SDL_Event& event) override;
  void initializeGL() override;
  void paintGL() override;
  void paintUI() override;
  void resizeGL(int width, int height) override;
  void terminateGL() override;

 private:
 
  int m_viewportWidth{};
  int m_viewportHeight{};
  float m_distancia{};

  GLuint m_objectsProgram{};

  Bola m_bola;

  Cenario m_cenario;

  Entrada m_Entrada;

  Obstaculos m_obstaculos;

  Aviao m_aviao;

  abcg::ElapsedTimer m_restartWaitTimer;

  std::default_random_engine m_randomEngine;

  void verificarColisoes();
  void restart();
  void update();
};

#endif