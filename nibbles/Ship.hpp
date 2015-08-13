#pragma once
#ifndef SHIP_HPP
#define SHIP_HPP

#include "Entity.hpp"
#include "EntityManager.hpp"

#define CONESHIP 0
#define DRONE 1

class Ship : public Entity
{
public:
	float speed;
	float maxThrust;
    int bulletType;
    Ship(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : Entity(position, rotationAxis, angle, scale), speed(0), maxThrust(1), bulletType(0) {}
    Ship() : Entity() {}
    virtual void initialize(int type, b2Vec2 initialVelocity);
    virtual void behavior();
	virtual void destructionEvent();
    virtual void fire();
	virtual void startContact(Entity* other, float dmg);
	virtual void endContact();
};

#endif