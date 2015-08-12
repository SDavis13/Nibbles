#pragma once
#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Entity.hpp"
#include "Ship.hpp"
#include "Debris.hpp"
#include "Bullet.hpp"
#include <Box2D/Dynamics/b2WorldCallbacks.h>

class EntityManager : public b2ContactListener
{

	//b2ContactListener
    // Called when two fixtures begin to touch
    virtual void BeginContact(b2Contact* contact);
  
    // Called when two fixtures cease to touch
    virtual void EndContact(b2Contact* contact);

	//static Entity *factory(int type);
	static Entity *factory(int type, glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale, b2Vec2 velocity);

};
#endif