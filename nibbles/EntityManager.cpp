#include "EntityManager.hpp"
#include "Entity.hpp"
#include "Box2D\Dynamics\Contacts\b2Contact.h"
#include <iostream>
#include <cmath>

void EntityManager::BeginContact(b2Contact* contact)
{
	//should get instance of Entity instead of -> -> a bunch
	b2Vec2 vlctA = contact->GetFixtureA()->GetBody()->GetLinearVelocity();
	b2Vec2 vlctB = contact->GetFixtureB()->GetBody()->GetLinearVelocity();
	b2Vec2 temp = vlctA-vlctB;
	float damage = temp.Length();
	Entity* tempA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
	Entity* tempB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
	tempA->startContact(tempB, damage);
	tempB->startContact(tempB, damage);
	std::cout << "begin";
}
void EntityManager::EndContact(b2Contact* contact)
{
	Entity* tempA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
	Entity* tempB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
	if(tempA->getHP() < 0){
		tempA->destructionEvent();
		delete tempA;
	}
	if(tempB->getHP() < 0){
		tempB->destructionEvent();
		delete tempB;
	}
	std::cout << "end";
}

void EntityManager::newEntity(int type, glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale, b2Vec2 velocity){
	characters.assign(1,factory(type, position, rotationAxis, angle, scale, velocity));
}

//private for now, everyone should be making requests to newEntity, not factory
Entity *EntityManager::factory(int type, glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale, b2Vec2 velocity){
	Entity* temp;
	switch(type){
	case 1: temp = (Entity*)new Ship(position, rotationAxis, angle, scale);
		break;
	case 2: temp = (Entity*)new Debris(position, rotationAxis, angle, scale);
		break;
	case 3: temp = (Entity*)new Bullet(position, rotationAxis, angle);
		break;
	default: temp = (Entity*)new Debris(position, rotationAxis, angle, scale);
	}
	temp->initialize(0, velocity);
	return temp;
}