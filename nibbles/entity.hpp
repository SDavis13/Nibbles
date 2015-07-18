#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

#include <glm/glm.hpp>

#include <Box2D/Dynamics/b2Body.h>

class Part;

class Entity
{
public:
    glm::vec3 position;
    glm::vec3 rotationAxis;
    float angle;
    glm::vec3 scale;
    std::vector<Part> parts;
    bool physValid;
    b2Body* body;
    Entity(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : position(position), rotationAxis(rotationAxis), angle(angle), scale(scale), physValid(false) {}
    Entity() : position(glm::vec3(0)), rotationAxis(glm::vec3(0,1,0)), angle(0), scale(glm::vec3(1)), physValid(false) {}
    void addPart(Part& part);
    void render(glm::mat4 transform);
    void render();
    void update();
};

#endif

