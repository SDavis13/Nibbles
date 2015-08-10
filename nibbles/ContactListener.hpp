#pragma once
#ifndef CONTACTLISTENER_HPP
#define CONTACTLISTENER_HPP

#include <Box2D/Dynamics/b2WorldCallbacks.h>

class ContactListener : public b2ContactListener
{
	//b2ContactListener
    // Called when two fixtures begin to touch
    virtual void BeginContact(b2Contact* contact);
  
    // Called when two fixtures cease to touch
    virtual void EndContact(b2Contact* contact);
};
#endif