#pragma once
#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entity.hpp"
#include "EntityManager.hpp"

#define BULLET 0
#define TEARSHOT 1

class Bullet : public Entity
{
public:
	float angle;
	float maxThrust;
	Bullet(glm::vec3 position, glm::vec3 rotationAxis, float angle) //overriding scale
            : Entity(position, rotationAxis, angle, glm::vec3 (0.1f, 0.1f, 0.1f)) {}
    Bullet() : Entity() {}
    virtual void initialize(int type, b2Vec2 initialVelocity);
    virtual void behavior();
	virtual void destructionEvent();
	virtual void startContact(Entity* other, float dmg);
	virtual void endContact();
};

#endif