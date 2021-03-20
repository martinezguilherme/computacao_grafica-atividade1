#include "aviao.hpp"

#include <cppitertools/itertools.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Aviao::initializeGL(GLuint program) {
    terminateGL();

    m_program = program;
    m_rotationLoc = glGetUniformLocation(m_program, "rotation");
    m_scaleLoc = glGetUniformLocation(m_program, "scale");
    m_translationLoc = glGetUniformLocation(m_program, "translation");

    m_translation = {0.0f, 0.7f};
    m_velocity = glm::vec2{-0.1f , 0.0f};
    m_rotation = 0;

    std::vector<glm::vec4> colors;
    // Frente avião
    m_positions.emplace_back(-0.15f, 0.0f);
    // Meio
    m_positions.emplace_back(0.0f, 0.0f);
    // Asa esquerda
    m_positions.emplace_back(0.07f, -0.02f);
    m_positions.emplace_back(0.09f, -0.02f);
    m_positions.emplace_back(0.02f, 0.0f);
    m_positions.emplace_back(0.0f, 0.0f);
    // Parte de tras
    m_positions.emplace_back(0.15f, 0.0f);
    m_positions.emplace_back(0.16f, 0.04f);
    m_positions.emplace_back(0.15f, 0.02f);
    // Meio das asa da direita
    m_positions.emplace_back(0.0f, 0.02f);
    m_positions.emplace_back(0.07f, 0.06f);
    m_positions.emplace_back(0.09f, 0.06f);
    m_positions.emplace_back(0.02f, 0.02f);
    // Restante da frente
    m_positions.emplace_back(-0.13f, 0.02f);

    for (size_t i = 0; i < 14; i++)
    {
            colors.push_back(glm::vec4(glm::vec4 (1.0f,
                                    1.0f,
                                    1.0f,
                                    0.8f)));
    }
   


    // Generate VBO posições
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_positions.size() * sizeof(glm::vec2), m_positions.data(),
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

void Aviao::paintGL(const Entrada &entrada) {


  glUseProgram(m_program);

  glBindVertexArray(m_vao);

  glUniform1f(m_scaleLoc, m_scale);
  glUniform1f(m_rotationLoc, m_rotation);
  glUniform2fv(m_translationLoc, 1, &m_translation.x);
  
  glDrawArrays(  GL_LINE_LOOP, 0, 14);

  glBindVertexArray(0);

  glUseProgram(0);
}

void Aviao::terminateGL() {
  glDeleteBuffers(1, &m_vbo);
  glDeleteVertexArrays(1, &m_vao);
}
//
void Aviao::update(const Entrada &entrada, float deltaTime) {
    m_translation += glm::vec2{deltaTime, deltaTime} * m_velocity;

}
