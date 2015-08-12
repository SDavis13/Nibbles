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

Entity *EntityManager::factory(int type, glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale, b2Vec2 velocity){
	switch(type){
	case 1: return(Entity*)new Ship(position, rotationAxis, angle, scale);
		break;
	case 2: return(Entity*)new Debris(position, rotationAxis, angle, scale);
		break;
	case 3: return(Entity*)new Bullet(position, rotationAxis, angle, velocity);
		break;
	default: return(Entity*)new Debris(position, rotationAxis, angle, scale);
	}
}