#pragma once
#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "Entity.hpp"

#define NIBBLERCORE 0

class Nibbler : public Entity
{	
public:
    static const int MAX_THRUST = 5;
    static const int MIN_SIZE = 1;
	glm::vec2 previouspos;
	glm::vec2 prepreviouspos;
    Nibbler(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : Entity(position, rotationAxis, angle, scale) {}
    Nibbler() : Entity() {}
    virtual void initialize(int type);
    virtual void behavior();
	b2Vec2 getGravity(float objMass, b2Vec2 objLoc);
	void applyThrust(b2Vec2 destination);
};

#endif