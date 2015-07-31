#include "Entity.hpp"
#include "Part.hpp"

void Entity::addPart(Part& part){
    parts.push_back(part);
}

void Entity::render(){
    for(int i = 0; i < parts.size(); ++i){
        parts[i].render();
    }
}

void Entity::render(glm::mat4 transform){
    for(int i = 0; i < parts.size(); ++i){
        parts[i].render(transform);
    }
}

void Entity::update(){
    angle = primeBody->GetAngle();
    b2Vec2 pos2d = primeBody->GetPosition();
    position.x = pos2d.x;
    position.z = pos2d.y;
    behavior();
}

void Entity::behavior(){}
