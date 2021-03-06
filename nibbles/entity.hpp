#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include <Box2D/Dynamics/b2Body.h>

class Part;

class Entity
{
public:
    glm::vec3 position;
    glm::vec3 rotationAxis;
    float angle;
    glm::vec3 scale;
    std::vector<Part*> parts;
    bool physValid;
    b2Body* primeBody;
    float mass;
    float energy;
	float hp;
    bool damage;
	int m_contacting;
    unsigned short centerMode; //unused at the moment
	Entity(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : position(position), rotationAxis(rotationAxis), angle(angle), scale(scale), physValid(false), mass(0), energy(0), hp(1), damage(true) {}
    Entity() : position(glm::vec3(0)), rotationAxis(glm::vec3(0,0,1)), angle(0), scale(glm::vec3(1)), physValid(false), hp(0) {}
    ~Entity();
    //Entity(const Entity& other) { printf("\nCopying entity at %f,%f,%f", position.x, position.y, position.z); }
    void addPart(Part* part);
    void render(glm::mat4 transform);
    void render();
    void update();
    virtual void initialize(int type, b2Vec2 velocity);
    virtual void behavior();
	virtual void destructionEvent();
	b2Vec2 getWorldCenter();
    glm::vec3 getGLCenter();
	float getHP();
	void applyDmg(float dmg);
	float getEnergy();
	virtual void startContact(Entity* other, float dmg);
	virtual void endContact();
};

#endif

