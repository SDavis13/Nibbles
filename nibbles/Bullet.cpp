#include "Bullet.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#include "Nibbler.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

void Bullet::initialize(int type, b2Vec2 initialVelocity){
    std::string name = "";
    b2FixtureDef fixDef;
    b2BodyDef bodDef;
    switch(type){
    case 0:
        name = "bullet";
        hp = 5.0f;
        fixDef.density = 20;
        fixDef.friction = 0.3;
        fixDef.restitution = 1;
        energy = -0.4;
        break;
    case 1:
        name = "tearshot";
        hp = 0.5f;
        fixDef.density = 0.5;
        fixDef.friction = 0.3;
        fixDef.restitution = 0;
        energy = -2;
        break;
    }
	m_contacting = 0;
    Part* bulletPart = new Part(*this, meshes[name], glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    bodDef.type = b2_dynamicBody;
    bodDef.fixedRotation = false;
	bodDef.linearVelocity = initialVelocity;
	bodDef.position = b2Vec2(position.x, position.y);
    bodDef.angle = angle*M_PI/180;
    std::vector<b2Shape*> shapes = bulletPart->computeShapes(false, 0);
    bulletPart->initialize(shapes, fixDef, bodDef);
    primeBody = bulletPart->body;
	primeBody->SetUserData((Entity*) this);
    mass = primeBody->GetMass();
    physValid = true;
}
void Bullet::behavior(){}
void Bullet::destructionEvent(){
	//pretty much nothing, shower of sparks?
}
void Bullet::startContact(Entity* other, float dmg){
	hp-=hp;
	m_contacting++;
}
void Bullet::endContact(){ m_contacting--;}