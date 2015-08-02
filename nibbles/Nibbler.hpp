#pragma once
#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "Entity.hpp"

#define NIBBLERCORE_OBJ 1

class Nibbler : public Entity
{	
	GLuint size;
	GLuint energy;
	glm::vec2 previouspos;
	glm::vec2 prepreviouspos;

    Nibbler(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : Entity(position, rotationAxis, angle, scale) {}
    Nibbler() : Entity() {}
    virtual void initialize(int type);
    virtual void behavior();
};

#endif