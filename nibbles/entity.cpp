#include "Entity.hpp"
#include "Part.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

Entity::~Entity(){
    while(!parts.empty()) 
        delete parts.back(), parts.pop_back();
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
    angle = (primeBody->GetAngle())*180/M_PI;
    b2Vec2 pos2d = primeBody->GetPosition();
    position.x = pos2d.x;
    position.z = pos2d.y;
    behavior();
}

void Entity::behavior(){}

void Entity::initialize(int type){}

b2Vec2 Entity::getWorldCenter(){
	return primeBody->GetWorldCenter();
}

glm::vec3 Entity::getGLCenter(){
    b2Vec2 location = primeBody->GetWorldCenter();
	return glm::vec3(location.x, 0, location.y);
}