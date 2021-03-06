#include "openglwindow.hpp"

#include <imgui.h>
#include "entrada.hpp"
#include "bola.hpp"

#include "abcg.hpp"

void OpenGLWindow::handleEvent(SDL_Event &event) {
  // Keyboard events
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_SPACE)
      m_Entrada.m_input.set(static_cast<size_t>(Input::Espaco));
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_Entrada.m_input.set(static_cast<size_t>(Input::Up));
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
      m_Entrada.m_input.set(static_cast<size_t>(Input::Down));
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_Entrada.m_input.set(static_cast<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_Entrada.m_input.set(static_cast<size_t>(Input::Right));
  }
  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_SPACE)
      m_Entrada.m_input.reset(static_cast<size_t>(Input::Espaco));
    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w)
      m_Entrada.m_input.reset(static_cast<size_t>(Input::Up));
    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s)
      m_Entrada.m_input.reset(static_cast<size_t>(Input::Down));
    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a)
      m_Entrada.m_input.reset(static_cast<size_t>(Input::Left));
    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d)
      m_Entrada.m_input.reset(static_cast<size_t>(Input::Right));
  }

  // Mouse events
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_RIGHT)
      m_Entrada.m_input.set(static_cast<size_t>(Input::Up));
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_RIGHT)
      m_Entrada.m_input.reset(static_cast<size_t>(Input::Up));
  }
  if (event.type == SDL_MOUSEMOTION) {
    glm::ivec2 mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

    glm::vec2 direction{glm::vec2{mousePosition.x - m_viewportWidth / 2,
                                  mousePosition.y - m_viewportHeight / 2}};
    direction.y = -direction.y;

    //printf("%f", direction.x);
    //m_aviao.setRotation(std::atan2(direction.y, direction.x) - M_PI_2);
    float deltaTime{static_cast<float>(getDeltaTime())};
    if (direction.x > 0)
      m_aviao.m_velocity[0] += 0.1f * deltaTime ;
    else
      m_aviao.m_velocity[0] += -0.1f * deltaTime;
    
    if (direction.y/2.0f > -0.5f)
      m_aviao.m_velocity[1] += 0.1f * deltaTime;
    else
      m_aviao.m_velocity[1] -= 0.1f * deltaTime;
    
  }
}

void OpenGLWindow::initializeGL() {

   // Create program to render the other objects
  m_objectsProgram = createProgramFromFile(getAssetsPath() + "objects.vert",
                                           getAssetsPath() + "objects.frag");

  glClearColor(0, 0, 0, 1);

  #if !defined(__EMSCRIPTEN__)
    glEnable(GL_PROGRAM_POINT_SIZE);
  #endif

  // Start pseudo-random number generator
  auto seed{std::chrono::steady_clock::now().time_since_epoch().count()};
  m_randomEngine.seed(seed);

  restart();
}

void OpenGLWindow::restart() {
    m_bola.initializeGL(m_objectsProgram);
    m_cenario.initializeGL(m_objectsProgram);
    m_obstaculos.initializeGL(m_objectsProgram);
    m_aviao.initializeGL(m_objectsProgram);
}

void OpenGLWindow::update() {
  float deltaTime{static_cast<float>(getDeltaTime())};
  m_bola.update(m_Entrada, deltaTime);
  m_cenario.update(m_Entrada, deltaTime);
  m_obstaculos.update(m_Entrada, deltaTime);
  m_aviao.update(m_Entrada, deltaTime);
  verificarColisoes();
  if(m_Entrada.m_input[static_cast<size_t>(Input::Espaco)]){
    restart();}
}

void OpenGLWindow::paintGL() {
  update();

  glClear(GL_COLOR_BUFFER_BIT);
  glViewport(0, 0, m_viewportWidth, m_viewportHeight);

   m_bola.paintGL(m_Entrada);
   m_cenario.paintGL(m_Entrada);
   m_obstaculos.paintGL(m_Entrada);
   m_aviao.paintGL(m_Entrada);

}

void OpenGLWindow::paintUI() {
  abcg::OpenGLWindow::paintUI();

  {
    auto size{ImVec2(300, 200)};
    auto position{ImVec2((m_viewportWidth - size.x) / 2.0f,
                         (m_viewportHeight - size.y) / 0.85f)};
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);
    ImGuiWindowFlags flags{ImGuiWindowFlags_NoBackground |
                           ImGuiWindowFlags_NoTitleBar };
    ImGui::Begin(" ", nullptr, flags);
    
    ImGui::Text("Dist??ncia do obstaculo: %f", m_distancia);
    ImGui::Text("Velocidade bolinha (x): %f", m_bola.m_velocity[0]);
    ImGui::Text("Velocidade avi??o (x): %f", m_aviao.m_velocity[0]);
    
    ImGui::Text("Aperte 'espa??o' para reiniciar");

    ImGui::PushItemWidth(150);
    ImGui::SliderFloat("Posi????o obstaculo (x)", &m_obstaculos.m_translation[0], -1.0f, 1.0f, "%f");
    ImGui::PopItemWidth();

    ImGui::End();
  }
}

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;

  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWindow::terminateGL() {
  glDeleteProgram(m_objectsProgram);

  m_bola.terminateGL();
  m_cenario.terminateGL();
  m_obstaculos.terminateGL();
  m_aviao.terminateGL();
}

void OpenGLWindow::verificarColisoes() {
  float deltaTime{static_cast<float>(getDeltaTime())};

  auto posicaoObstaculo{m_obstaculos.m_translation};
  auto posicaoBola{m_bola.m_translation};

  auto distance{glm::distance(posicaoBola, posicaoObstaculo)};
  m_distancia = distance;

  // Simula transferencia de energia entre os objetos ap??s colis??o
  if (distance < 0.23f) {
    glm::vec2 velocidadeImpacto = m_bola.m_velocity * 0.7f * glm::vec2(1, 0);
    m_obstaculos.m_velocity += velocidadeImpacto;
    m_bola.m_velocity -= ((m_bola.m_velocity * 1.1f) + glm::vec2(0, -0.05f) ) * 1.5f;

    // Da velocidade algular para o obstaculo ap??s colis??o
    m_obstaculos.m_velocidadeAngular += m_bola.m_velocity[0] * 0.4f;
  }




}
