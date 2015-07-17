#pragma once
#ifndef GLOBALS_HPP
#define GLOBALS_HPP

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>

#include <Box2d/Dynamics/b2World.h>
#include <Box2d/Common/b2Math.h>

#ifdef GLOBALS_CPP
#define COMPILE_HERE
#else
#define COMPILE_HERE extern
#endif

COMPILE_HERE GLFWwindow* window;

COMPILE_HERE b2World* universe;

COMPILE_HERE std::vector<unsigned short> indices;
COMPILE_HERE std::vector<glm::vec3> indexed_vertices;
COMPILE_HERE std::vector<glm::vec2> indexed_uvs;
COMPILE_HERE std::vector<glm::vec3> indexed_normals;

COMPILE_HERE glm::mat4 projectionMatrix;
COMPILE_HERE glm::mat4 viewMatrix;
COMPILE_HERE glm::mat4 mvp;

COMPILE_HERE GLuint programID;

COMPILE_HERE GLuint MatrixID;
COMPILE_HERE GLuint ViewMatrixID;
COMPILE_HERE GLuint ModelMatrixID;
COMPILE_HERE GLuint LightMatrixID;

COMPILE_HERE GLuint LightID;
COMPILE_HERE GLuint LightColorID;

COMPILE_HERE GLuint vertexPosition_modelspaceID;
COMPILE_HERE GLuint vertexUVID;
COMPILE_HERE GLuint vertexNormal_modelspaceID;

COMPILE_HERE GLuint vertexbuffer;
COMPILE_HERE GLuint uvbuffer;
COMPILE_HERE GLuint normalbuffer;
COMPILE_HERE GLuint elementbuffer;

COMPILE_HERE GLuint Texture;
COMPILE_HERE GLuint TextureID;

int initializeOGLstuff();

int floatSign(float val);

#endif