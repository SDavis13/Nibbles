#pragma once
#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <GL/glew.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

class Mesh
{
public:
    GLuint startindex;
    GLuint startvertex;
    GLuint numindices;
    GLuint numvertices;
    bool valid;
    Mesh(const char * path);
    Mesh() : valid(false) {}
    std::vector<b2Vec2> computeHullPoly();
    float computeMaxRadius();
};

#endif