#pragma once
#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Entity.hpp"
#include <Box2D/Dynamics/b2WorldCallbacks.h>

enum type {
	BULLET,
	DEBRIS,
	SHIP
};

class EntityManager : public b2ContactListener
{
	//b2ContactListener
    // Called when two fixtures begin to touch
    virtual void BeginContact(b2Contact* contact);
  
    // Called when two fixtures cease to touch
    virtual void EndContact(b2Contact* contact);

	static Entity *factory(enum type);
};
#endif