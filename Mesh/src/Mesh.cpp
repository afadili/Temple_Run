#include <Mesh/Mesh.hpp>

Mesh::Mesh(const std::vector<ShapeVertex> &vertices) : m_vertices(vertices) {
}

Mesh::Mesh(const std::vector<ShapeVertex> &vertices, const std::vector<int> &indexVer)
: m_vertices(vertices), m_indexVer(indexVer) {
}

Mesh::Mesh(const std::vector<ShapeVertex> &vertices, ShaderManager *shader, Texture *texture)
: m_vertices(vertices), m_shader(shader), m_texture(texture) {
}

Mesh::Mesh(ShaderManager *shader, Texture *texture)
: m_shader(shader), m_texture(texture) {
}

Mesh::Mesh(const std::vector<ShapeVertex> &vertices, const std::vector<int> &indexVer, ShaderManager *shader, Texture *texture)
: m_vertices(vertices), m_indexVer(indexVer), m_shader(shader), m_texture(texture) {
}

Mesh::~Mesh() {
  delete m_vbo;
  delete m_ibo;
  delete m_vao;
}

void Mesh::bind() const {
  m_vao->bind(); // VAO
  m_shader->use(); // Shader program
  m_texture->bind(); // Texture
}

void Mesh::debind() const {
  m_texture->debind(); // Texture
  m_vao->debind(); // VAO
}

void Mesh::draw() const {
  if (haveIBO())
    glDrawElements(GL_TRIANGLES, m_indexVer.size(), GL_UNSIGNED_INT, 0);
  else
    glDrawArrays(GL_TRIANGLES, 0, vertexCount());
}

void Mesh::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MWMatrix, const glm::mat4 &ViewMatrix) const {
    // sends uniform variables
    m_shader->sendUniformMatrix4fv("uMVPMatrix", ProjMatrix * ViewMatrix * MWMatrix);
    m_shader->sendUniformMatrix4fv("uMVMatrix", ViewMatrix * MWMatrix);
    m_shader->sendUniformMatrix4fv("uNormalMatrix", glm::inverse(MWMatrix));
    m_shader->sendUniform1i("uTexture", 0);

    // draw the mesh
    draw();
  }


void Mesh::fillBuffers() {
  m_vbo->fillBuffer(m_vertices);
  if (haveIBO()) {
    m_ibo->fillBuffer(m_indexVer);
    m_vao->fillBuffer(m_vertices, m_vbo, m_ibo);
  } else {
    m_vao->fillBuffer(m_vertices, m_vbo);
  }
}

