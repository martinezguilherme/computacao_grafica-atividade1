#include "bola.hpp"

#include <cppitertools/itertools.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Bola::initializeGL(GLuint program) {
  terminateGL();

  m_program = program;
  m_rotationLoc = glGetUniformLocation(m_program, "rotation");
  m_scaleLoc = glGetUniformLocation(m_program, "scale");
  m_translationLoc = glGetUniformLocation(m_program, "translation");

  auto nLados = 50;

  m_rotation = 0.0f;
  m_translation = {-0.45f, -0.45f};
  m_velocity = glm::vec2(0);

  auto seed{std::chrono::steady_clock::now().time_since_epoch().count()};
  m_randomEngine.seed(seed);
  std::vector<glm::vec4> colors(0);

  std::uniform_real_distribution<float> aletoriasCores(0.0f, 1.0f);

   // Create geometry e cores aleatorias
  std::vector<glm::vec2> positions(0);
  positions.emplace_back(0, 0);
  auto step{M_PI * 2 / nLados};
  for (auto angle : iter::range(0.0, M_PI * 2, step)) {
    auto radius{1};
    colors.push_back(glm::vec4 (aletoriasCores(m_randomEngine),
                               aletoriasCores(m_randomEngine),
                               aletoriasCores(m_randomEngine),
                               0.5f));
    positions.emplace_back(radius * std::cos(angle), radius * std::sin(angle));
  }
  positions.push_back(positions.at(1));

  // Generate VBO posições
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec2), positions.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate VBO of colors
  glGenBuffers(1, &m_vboCores);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboCores);
  glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec4),
               colors.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);


  // Get location of attributes in the program
  GLint positionAttribute{glGetAttribLocation(m_program, "inPosition")};
  GLint colorAttribute{glGetAttribLocation(m_program, "inColor")};

  // Create VAO
  glGenVertexArrays(1, &m_vao);

  // Bind vertex attributes to current VAO
  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glEnableVertexAttribArray(positionAttribute);
  glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glEnableVertexAttribArray(colorAttribute);
  glBindBuffer(GL_ARRAY_BUFFER, m_vboCores);
  glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  glBindVertexArray(0);
}

void Bola::paintGL(const Entrada &entrada) {


  glUseProgram(m_program);

  glBindVertexArray(m_vao);

  glUniform1f(m_scaleLoc, m_scale);
  glUniform1f(m_rotationLoc, m_rotation);
  glUniform2fv(m_translationLoc, 1, &m_translation.x);
  
  glDrawArrays(GL_TRIANGLE_FAN, 0, 52);

  glBindVertexArray(0);

  glUseProgram(0);
}

void Bola::terminateGL() {
  glDeleteBuffers(1, &m_vbo);
  glDeleteVertexArrays(1, &m_vao);
}

void Bola::update(const Entrada &entrada, float deltaTime) {
  if (entrada.m_input[static_cast<size_t>(Input::Right)])
    m_velocity += glm::vec2{1.0f * deltaTime, 0};
  if (entrada.m_input[static_cast<size_t>(Input::Left)])
    m_velocity -= glm::vec2{1.0f * deltaTime, 0};

  m_rotation = glm::wrapAngle(m_rotation - 4.0f * deltaTime * m_velocity[0]);
  m_translation += m_velocity * deltaTime;
  if (m_velocity[0] > 0)
    m_velocity -= deltaTime * glm::vec2{5.2f * deltaTime, 0};
  if (m_velocity[0] < 0)
    m_velocity += deltaTime * glm::vec2{5.2f * deltaTime, 0};

  // Retorna a bolinha para o solo
  if (m_translation[1] >= -0.45f)
    m_velocity -= glm::vec2{0, 0.2f * deltaTime};
  else
    m_velocity = glm::vec2{m_velocity[0], 0};

}
