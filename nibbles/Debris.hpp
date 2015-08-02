#pragma once
#ifndef DEBRIS_HPP
#define DEBRIS_HPP

#include "Entity.hpp"

#define DEBRIS1_OBJ 2

class Debris : Entity
{
public:
	GLuint size;
	GLuint energy;

    Debris(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : Entity(position, rotationAxis, angle, scale) {}
    Debris() : Entity() {}
    virtual void initialize(int type);
    virtual void behavior();

};

#endif