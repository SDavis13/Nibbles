#pragma once
#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "Entity.hpp"

#define NIBBLERCORE_OBJ 1

class Nibbler : public Entity
{	
public:
	glm::vec2 previouspos;
	glm::vec2 prepreviouspos;
    Nibbler(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : Entity(position, rotationAxis, angle, scale) {}
    Nibbler() : Entity() {}
    virtual void initialize(int type);
    virtual void behavior();
	float getGravityStrength(float mass, float distance);
	void applyThrust(glm::vec2 point){}
};

#endif