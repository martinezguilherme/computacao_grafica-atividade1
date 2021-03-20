#include "obstaculos.hpp"

#include <cppitertools/itertools.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/rotate_vector.hpp>

void Obstaculos::initializeGL(GLuint program) {
    terminateGL();

    m_program = program;
    m_rotationLoc = glGetUniformLocation(m_program, "rotation");
    m_scaleLoc = glGetUniformLocation(m_program, "scale");
    m_translationLoc = glGetUniformLocation(m_program, "translation");

    m_translation = {-0.1f, -0.57f};

    std::vector<glm::vec4> colors;
    std::vector<glm::vec2> positions;
    positions.emplace_back(0.5f, 0.5f);
    positions.emplace_back(0.75f, 0.5f);
    positions.emplace_back(0.75f, 0.0f);
    positions.emplace_back(0.5f, 0.0f);
    positions.emplace_back(0.75f, 0.0f);
    positions.emplace_back(0.5f, 0.5f);

   // Create geometry e cores aleatorias
    colors.push_back(glm::vec4(glm::vec4 (0.8f,
                               0.5f,
                               0.8f,
                               0.8f)));
    colors.push_back(glm::vec4(glm::vec4 (0.4f,
                               0.2f,
                               0.3f,
                               0.8f)));
    colors.push_back(glm::vec4(glm::vec4 (0.4f,
                               0.3f,
                               0.3f,
                               0.8f)));
    colors.push_back(glm::vec4(glm::vec4 (0.4f,
                               0.6f,
                               0.8f,
                               0.6f)));
    colors.push_back(glm::vec4(glm::vec4 (0.4f,
                               0.6f,
                               0.8f,
                               0.6f)));
    colors.push_back(glm::vec4(glm::vec4 (0.4f,
                               0.6f,
                               0.8f,
                               0.6f)));

  //positions.push_back(positions.at(1));

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

void Obstaculos::paintGL(const Entrada &entrada) {


  glUseProgram(m_program);

  glBindVertexArray(m_vao);

  glUniform1f(m_scaleLoc, m_scale);
  glUniform1f(m_rotationLoc, m_rotation);
  glUniform2fv(m_translationLoc, 1, &m_translation.x);
  
  glDrawArrays(  GL_TRIANGLES, 0, 6);

  glBindVertexArray(0);

  glUseProgram(0);
}

void Obstaculos::terminateGL() {
  glDeleteBuffers(1, &m_vbo);
  glDeleteVertexArrays(1, &m_vao);
}
//
void Obstaculos::update(const Entrada &entrada, float deltaTime) {
    m_translation += glm::vec2{deltaTime, 0.0f} * m_velocity;
    if (m_velocity[0] > 0.0f){
        m_velocity -= glm::vec2{0.1f * deltaTime, 0.0f};
    } 
    else{
        m_velocity = glm::vec2{0.0f, 0.0f};
    }
}
