#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <glfw3.h>
#include "globals.hpp"
#include <Box2d/Dynamics/b2Body.h>
#include <Box2d/Dynamics/b2World.h>

namespace nibbles{
    class Entity
    {
    public:
        b2Body* body;
        GLuint vertex_index;
        GLuint num_vertexes;
        Entity(b2World* theWorld);
        ~Entity(void);
        virtual void iterate() = 0;
    };
}
#endif