#include <vector>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

#include "Mesh.hpp"
#include "globals.hpp"

Mesh::Mesh(const char * path)
{
    valid = true;
    startindex = (GLuint)indices.size();
    startvertex = (GLuint)indexed_vertices.size();
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
    bool res = loadOBJ(path, vertices, uvs, normals);
    indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
    numindices = (GLuint)indices.size() - startindex;
    numvertices = (GLuint)indexed_vertices.size() - startvertex;
}
