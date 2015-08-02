#pragma once
#ifndef SHIP_HPP
#define SHIP_HPP

#include "Entity.hpp"

#define CONESHIP_OBJ 0

class Ship : Entity
{
public:
	GLuint size;
	GLuint energy;

    Ship(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : Entity(position, rotationAxis, angle, scale) {}
    Ship() : Entity() {}
    virtual void initialize(int type);
    virtual void behavior();
};

#endif