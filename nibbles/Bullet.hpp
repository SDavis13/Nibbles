#pragma once
#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entity.hpp"

#define BULLET 0
#define TEARSHOT 1

class Bullet : public Entity
{
public:
	b2Vec2 initialVelocity;
	float angle;
	float maxThrust;
	Bullet(glm::vec3 position, glm::vec3 rotationAxis, float angle, b2Vec2 velocity ) //overriding scale
            : Entity(position, rotationAxis, angle, glm::vec3 (0.1f, 0.1f, 0.1f)), initialVelocity(velocity) {}
    Bullet() : Entity() {}
    virtual void initialize(int type);
    virtual void behavior();
	virtual void destructionEvent();
	void Nibbler::startContact(Entity* other, float dmg){}
	void Nibbler::endContact(){}
};

#endif