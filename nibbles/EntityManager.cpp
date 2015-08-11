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
	//float damage = sqrt(pow((vlctA.x-vlctB.x),2)+pow((vlctA.y-vlctB.y),2));
	b2Vec2 temp = vlctA-vlctB;
	float damage = temp.Length();
	Entity* tempA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
	Entity* tempB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
	tempA->startContact(tempB, damage);
	tempB->startContact(tempB, damage);
	std::cout << "begin/n";
	//if hp < 0, add to destruction list
}
void EntityManager::EndContact(b2Contact* contact)
{
	//destroy Entities in destruction list
	//make sure destructors create things if needed
	std::cout << "end/n";
}
