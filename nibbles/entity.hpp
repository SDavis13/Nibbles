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
	int m_contacting;
    unsigned short centerMode; //unused at the moment
    Entity(glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale) 
            : position(position), rotationAxis(rotationAxis), angle(angle), scale(scale), physValid(false), mass(0), energy(0) {}
    Entity() : position(glm::vec3(0)), rotationAxis(glm::vec3(0,1,0)), angle(0), scale(glm::vec3(1)), physValid(false) {}
    ~Entity();
    //Entity(const Entity& other) { printf("\nCopying entity at %f,%f,%f", position.x, position.y, position.z); }
    void addPart(Part* part);
    void render(glm::mat4 transform);
    void render();
    void update();
    virtual void initialize(int type);
    virtual void behavior();
	b2Vec2 getWorldCenter();
    glm::vec3 getGLCenter();
	void startContact() { m_contacting++; }
	void endContact() { m_contacting--; }
};

#endif

