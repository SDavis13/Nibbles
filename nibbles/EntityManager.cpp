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
	std::cout << type::BULLET;
}
void EntityManager::EndContact(b2Contact* contact)
{
	Entity* tempA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
	Entity* tempB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
	if(tempA->getHP() < 0){
		tempA->destructionEvent();
		//delete tempA;
	}
	if(tempB->getHP() < 0){
		tempB->destructionEvent();
		//delete tempB;
	}
	std::cout << type::DEBRIS;
}

Entity *EntityManager::factory(enum type){

	/*
		switch(type){
	case 0: return ;
		break;
	case 1:
		break;
	case 2:
		break;
	default:

	}*/
}
