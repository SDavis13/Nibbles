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
    bool hullValid;
    std::vector<std::vector<b2Vec2> > hullPoly;
    float maxRadius;
    Mesh(const char * path);
    Mesh() : valid(false), hullValid(false) {}
    void computeHull();
    std::vector<std::vector<b2Vec2> > & getHullPoly();
    float getRadius();
};

#endif