#include "EntityManager.hpp"
#include "Entity.hpp"
#include "Nibbler.hpp"
#include "Box2D\Dynamics\Contacts\b2Contact.h"
#include <iostream>
#include <cmath>

void EntityManager::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
	b2Vec2 temp = (bodyA->GetLinearVelocity()) - (bodyB->GetLinearVelocity());
	float damage = temp.Length();
	Entity* tempA = (Entity*)(bodyA->GetUserData());
	Entity* tempB = (Entity*)(bodyB->GetUserData());
	tempA->startContact(tempB, damage);
	tempB->startContact(tempA, damage);
	std::cout << "begin";
}
void EntityManager::EndContact(b2Contact* contact)
{
	Entity* tempA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
	Entity* tempB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
	if(tempA->getHP() < 0){
		if(tempA != (Entity*) player){
		    deletionList.insert(tempA);
            entityList.erase(tempA);
        }
	}
	if(tempB->getHP() < 0){
        if(tempB != (Entity*) player){
		    deletionList.insert(tempB);
            entityList.erase(tempB);
        }
	}
	std::cout << "end";
}

void EntityManager::update(){
    if(!deletionList.empty()){
        for (std::set<Entity*>::iterator it = deletionList.begin(); it != entityList.end(); ++it){
            Entity* item = *it;
            entityList.erase(it);
            --it;
            item->destructionEvent();
            delete item;
        }
    }
    b2Body* bodies = universe->GetBodyList();
    while(bodies != NULL){
        if(bodies != player->primeBody){
            bodies->ApplyForceToCenter( ( player->getGravity(bodies->GetMass(), bodies->GetPosition()) ), true);
        }
        bodies = bodies->GetNext();
    }
    for (std::set<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it){
        Entity* item = *it;
        item->update();
    }
    player->update();
}

void EntityManager::render(){
    background->render();
    for (std::set<Entity*>::iterator it = entityList.begin(); it != entityList.end(); ++it){
        Entity* item = *it;
        item->render();
    }
    player->render();
}

void EntityManager::newEntity(int type, glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale, b2Vec2 velocity){
	//characters.assign(1,factory(type, position, rotationAxis, angle, scale, velocity));
}

//private for now, everyone should be making requests to newEntity, not factory
Entity *EntityManager::factory(int type, glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale, b2Vec2 velocity){
	Entity* temp;
	switch(type){
	case 1: temp = (Entity*)new Ship(position, rotationAxis, angle, scale);
		break;
	case 2: temp = (Entity*)new Debris(position, rotationAxis, angle, scale);
		break;
	case 3: temp = (Entity*)new Bullet(position, rotationAxis, angle, scale);
		break;
	default: temp = (Entity*)new Debris(position, rotationAxis, angle, scale);
	}
	temp->initialize(0, velocity);
	return temp;
}