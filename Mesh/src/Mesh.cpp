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

void Mesh::fillBuffers() {
  m_vbo->fillBuffer(m_vertices);
  if (haveIBO()) {
    m_ibo->fillBuffer(m_indexVer);
    m_vao->fillBuffer(m_vertices, m_vbo, m_ibo);
  } else {
    m_vao->fillBuffer(m_vertices, m_vbo);
  }
}

