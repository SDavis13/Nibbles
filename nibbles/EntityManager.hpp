#pragma once
#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "globals.hpp"

#include "Entity.hpp"
#include "Ship.hpp"
#include "Debris.hpp"
#include "Bullet.hpp"
#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <set>

class EntityManager : public b2ContactListener
{
    std::set<Entity*> entityList;
    std::set<Entity*> deletionList;

	//b2ContactListener
    // Called when two fixtures begin to touch
    virtual void BeginContact(b2Contact* contact);
  
    // Called when two fixtures cease to touch
    virtual void EndContact(b2Contact* contact);

	//request for new entities
	void newEntity(int type, glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale, b2Vec2 velocity);
private:
	//static Entity *factory(int type);
	static Entity *factory(int type, glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale, b2Vec2 velocity);

};
#endif