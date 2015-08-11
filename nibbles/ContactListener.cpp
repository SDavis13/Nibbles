#include "ContactListener.hpp"
#include "Entity.hpp"
#include "Box2D\Dynamics\Contacts\b2Contact.h"
#include <iostream>
#include <cmath>

void ContactListener::BeginContact(b2Contact* contact)
{
	//should get instance of Entity instead of -> -> a bunch
	b2Vec2 vlctA = contact->GetFixtureA()->GetBody()->GetLinearVelocity();
	b2Vec2 vlctB = contact->GetFixtureB()->GetBody()->GetLinearVelocity();
	//float damage = sqrt(pow((vlctA.x-vlctB.x),2)+pow((vlctA.y-vlctB.y),2));
	b2Vec2 temp = vlctA-vlctB;
	float damage = temp.Length();
	void* tempA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* tempB = contact->GetFixtureB()->GetBody()->GetUserData();
	std::cout << "begin/n";
	//subtract damage from both
	//if hp < 0, add to destruction list
}
void ContactListener::EndContact(b2Contact* contact)
{
	//destroy Entities in destruction list
	//make sure destructors create things if needed
	std::cout << "end/n";
}
