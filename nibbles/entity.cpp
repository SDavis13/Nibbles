#include "Entity.hpp"
#include "Part.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

Entity::~Entity(){
    for(int i = 0; i < parts.size(); ++i){
        delete parts[i];
        parts[i] = NULL;
    }
    parts.clear();
    primeBody = NULL;
}

void Entity::addPart(Part* part){
    parts.push_back(part);
}

void Entity::render(){
    for(int i = 0; i < parts.size(); ++i){
        parts[i]->render();
    }
}

void Entity::render(glm::mat4 transform){
    for(int i = 0; i < parts.size(); ++i){
        parts[i]->render(transform);
    }
}

void Entity::update(){
    if(physValid){
        for(unsigned int i = 0; i < parts.size(); ++i){
            Part* curPart = parts[i];
            b2Body* curBody = curPart->body;
            curPart->angle = (curBody->GetAngle())*180/M_PI;
            b2Vec2 pos2d = curBody->GetPosition();
            curPart->position.x = pos2d.x;
            curPart->position.y = pos2d.y;
        }
        behavior();
    }
}

void Entity::behavior(){}

void Entity::initialize(int type, b2Vec2 velovity){}

void Entity::destructionEvent() {}

b2Vec2 Entity::getWorldCenter(){
	return primeBody->GetWorldCenter();
}

glm::vec3 Entity::getGLCenter(){
    b2Vec2 location = primeBody->GetWorldCenter();
	return glm::vec3(location.x, location.y, 0);
}

float Entity::getHP(){
	return hp;
}
void Entity::applyDmg(float dmg){
	hp-=dmg;
}
float Entity::getEnergy(){
	return energy;
}
void Entity::startContact(Entity* other, float dmg){}
void Entity::endContact(){}
