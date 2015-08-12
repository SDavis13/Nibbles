#pragma once
#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "Entity.hpp"
#include "EntityManager.hpp"

#define NIBBLERCORE 0

class Nibbler : public Entity
{	
public:
    static const int MIN_SIZE = 1;
	glm::vec2 previouspos;
	glm::vec2 prepreviouspos;
    Nibbler(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : Entity(position, rotationAxis, angle, scale) {}
    Nibbler() : Entity() {}
    virtual void initialize(int type, b2Vec2 initialVelocity);
    virtual void behavior();
	b2Vec2 getGravity(float objMass, b2Vec2 objLoc);
	void applyThrust(b2Vec2 destination);
	virtual void destructionEvent();
	virtual void startContact(Entity* other, float dmg);
	virtual void endContact();
};

#endif