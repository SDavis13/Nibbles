#pragma once
#ifndef DEBRIS_HPP
#define DEBRIS_HPP

#include "Entity.hpp"

#define RANDOM 0
#define DEBRIS1 1
#define DEBRIS2 2
#define DEBRIS3 3
#define CANISTER 4

class Debris : public Entity
{
public:
    Debris(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : Entity(position, rotationAxis, angle, scale) {}
    Debris() : Entity() {}
    virtual void initialize(int type);
	static int randDebrisType();
    virtual void behavior();
	virtual void destructionEvent();
	void Nibbler::startContact(Entity other, float dmg){}
	void Nibbler::endContact(){}
};

#endif