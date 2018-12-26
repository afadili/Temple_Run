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

Mesh::Mesh(const glimac::FilePath &objPath) {
  loadObj(objPath);
}

Mesh::~Mesh() {
  delete m_vbo;
  delete m_ibo;
  delete m_vao;
}

void Mesh::bind() const {
  m_vao->bind(); // VAO
  m_shader->use(); // Shader program
  if (m_texture)
    m_texture->bind(); // Texture
}

void Mesh::debind() const {
  if (m_texture)
    m_texture->debind(); // Texture
  m_vao->debind(); // VAO
}

void Mesh::draw() const {
  if (haveIBO())
    glDrawElements(GL_TRIANGLES, m_indexVer.size(), GL_UNSIGNED_INT, 0);
  else
    glDrawArrays(GL_TRIANGLES, 0, vertexCount());
}

void Mesh::draw(const glm::mat4 &ProjMatrix, const glm::mat4 &MWMatrix, const glm::mat4 & ViewMatrix) const {
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

void Mesh::loadObj(const glimac::FilePath &objPath) {

  // FILE ERRORS
  std::ifstream objFile(objPath, std::ifstream::binary);
  if (objFile.fail())
    throw Error("The object file \"" + objPath.str() + "\" is not found !", "FILE_NOT_FOUND", true);

  if (objPath.ext() != "obj")
    throw Error("The file \"" + objPath.str() + "\" as to be a .obj file !", "INCORRECT_FILE", true);

  // Temporary variables in which the contents of the .obj are stored
  std::vector< unsigned int > uvIndices, normalIndices;
  std::vector< glm::vec3 > temp_vertices;
  std::vector< glm::vec2 > temp_uvs;
  std::vector< glm::vec3 > temp_normals;

  // GET OBJECT DATA  
  std::string lineHeader; // the first word of the line
  while (objFile >> lineHeader) {

    // Trim newline '\r\n' or '\n'
    if (lineHeader.size() > 0) {
      if (lineHeader[lineHeader.size() - 1] == '\n') lineHeader.erase(lineHeader.size() - 1);
    }
    if (lineHeader.size() > 0) {
      if (lineHeader[lineHeader.size() - 1] == '\r') lineHeader.erase(lineHeader.size() - 1);
    }

    // Skip if empty line.
    if (lineHeader.empty()) {
      continue;
    }

    // Skip leading space.
    const char* token = lineHeader.c_str();
    token += strspn(token, " \t");

    assert(token);
    if (token[0] == '\0') continue; // empty line

    if (token[0] == '#') continue; // comment line


    // vertex
    if (lineHeader.compare("v") == 0) {
      glm::vec3 vertex;
      objFile >> vertex.x;
      objFile >> vertex.y;
      objFile >> vertex.z;
      temp_vertices.push_back(vertex);
      continue;
    }

    // textures
    if (lineHeader.compare("vt") == 0) {
      glm::vec2 uv;
      objFile >> uv.x;
      objFile >> uv.y;
      temp_uvs.push_back(uv);
      continue;
    }

    // normals
    if (lineHeader.compare("vn") == 0) {
      glm::vec3 normal;
      objFile >> normal.x;
      objFile >> normal.y;
      objFile >> normal.z;
      temp_normals.push_back(normal);
      continue;
    }

    // faces
    if (lineHeader.compare("f") == 0) {
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

      for (int i = 0; i < 3; i++) {
        std::string tmp;
        std::getline(objFile, tmp, '/');
        vertexIndex[i] = std::stoi(tmp);
        std::getline(objFile, tmp, '/');
        uvIndex[i] = std::stoi(tmp);
        objFile >> normalIndex[i];
      }


      m_indexVer.push_back(vertexIndex[0]);
      m_indexVer.push_back(vertexIndex[1]);
      m_indexVer.push_back(vertexIndex[2]);
      uvIndices.push_back(uvIndex[0]);
      uvIndices.push_back(uvIndex[1]);
      uvIndices.push_back(uvIndex[2]);
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);
    }
  }

  // INDEXING
  for (unsigned int i = 0; i < m_indexVer.size(); i++) { // For each vertex of each triangle
    unsigned int vertexIndex = m_indexVer[i];
    ShapeVertex shape(temp_vertices[ vertexIndex - 1 ], temp_normals[ vertexIndex - 1 ], temp_uvs[ vertexIndex - 1 ]);
    m_vertices.push_back(shape);
  }


}