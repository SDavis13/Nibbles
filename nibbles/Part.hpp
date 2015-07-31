#pragma once
#ifndef PART_HPP
#define PART_HPP

#include <glm/glm.hpp>

#include "globals.hpp"
#include "Mesh.hpp"
#include "Entity.hpp"

#ifdef PART_CPP
Entity defaultEntity;
#else
extern Entity defaultEntity;
#endif

class Part
{
public:
    Entity& whole;
    glm::vec3 position;
    glm::vec3 rotationAxis;
    float angle;
    glm::vec3 scale;
    Mesh mesh;
    bool valid;
    bool physValid;
    b2Body* body;
    std::vector<b2Fixture*> fixtures;
    std::vector<b2Shape*> shapes;
    Part(Entity& source, Mesh& mesh, glm::vec3 relPosition = glm::vec3(0), glm::vec3 relRotAxis = glm::vec3(0,1,0), 
            float relAngle = 0, glm::vec3 relScale = glm::vec3(1)) : 
                whole(source), position(relPosition), rotationAxis(relRotAxis), angle(relAngle), 
                    scale(relScale), mesh(mesh), valid(true), physValid(false) {source.addPart(*this); }
    Part() : whole(defaultEntity), valid(false), physValid(false) {}
    ~Part() { if(physValid) universe->DestroyBody(body); }
    void render(glm::mat4& model) const;
    void render() const;
    glm::mat4 generateTransform() const;
    void generateTransform(glm::mat4& transform) const;
    void Part::computeShapes(bool circular = false, float offset = 0);
};

#endif

