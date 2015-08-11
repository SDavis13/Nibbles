#pragma once
#ifndef PART_HPP
#define PART_HPP

#include <glm/glm.hpp>

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

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
    float opacity;
    Mesh mesh;
    bool valid;
    bool physValid;
    b2Body* body;
    Part(Entity& source, Mesh& mesh, glm::vec3 relPosition = glm::vec3(0), glm::vec3 relRotAxis = glm::vec3(0,0,1), 
            float relAngle = 0, glm::vec3 relScale = glm::vec3(1)) : 
                whole(source), position(relPosition), rotationAxis(relRotAxis), angle(relAngle), 
                    scale(relScale), mesh(mesh), valid(true), physValid(false), opacity(1.0f) {source.addPart(this); }
    Part() : whole(defaultEntity), valid(false), physValid(false) {}
    ~Part() { if(physValid) universe->DestroyBody(body); }
    //Part(const Part& other) { printf("Copying Part"); }
    void render(glm::mat4& model) const;
    void render() const;
    glm::mat4 generateTransform() const;
    void generateTransform(glm::mat4& transform) const;
    std::vector<b2Shape*> computeShapes(bool circular = false, float offset = 0);
    void initialize(std::vector<b2Shape*>& shapes, b2FixtureDef fixDefinition, b2BodyDef bodyDefinition);
};

#endif

