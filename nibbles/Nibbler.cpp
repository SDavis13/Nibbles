#include "Nibbler.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2Body.h>

void Nibbler::initialize(int type, b2Vec2 initialVelocity){
    Part* core = new Part(*this, meshes["nibblercore"], glm::vec3(0), glm::vec3(0,0,1), 0, glm::vec3(MIN_SIZE));
    Part* corona = new Part(*this, meshes["nibblercorona"], glm::vec3(0), glm::vec3(0,0,1), 0, glm::vec3(MIN_SIZE));
    corona->opacity = 0.1;
    b2FixtureDef fixDef;
    fixDef.density = 10;
    b2BodyDef bodDef;
    bodDef.type = b2_dynamicBody;
    bodDef.fixedRotation = true;
    bodDef.position = b2Vec2(position.x, position.y);
    bodDef.angle = angle*M_PI/180;
    bodDef.linearVelocity = initialVelocity;
	bodDef.linearDamping = 10;
    std::vector<b2Shape*> shapes = core->computeShapes(false, 0);
    core->initialize(shapes, fixDef, bodDef);
    primeBody = core->body;
	primeBody->SetUserData((Entity*) this);
    mass = primeBody->GetMass();
	hp = 10.0f;
    energy = MIN_SIZE;
    physValid = true;
	m_contacting = 0;
}
b2Vec2 Nibbler::getGravity(float objMass, b2Vec2 objLoc){
    b2Vec2 difference = primeBody->GetWorldCenter() - objLoc;
    float distanceSqr = difference.LengthSquared();
    float force = mass*objMass/distanceSqr * 100000;
    difference.Normalize();
    difference *= force;
    return difference;
}
void Nibbler::behavior(){
}
void Nibbler::applyThrust(b2Vec2 destination){
    float scalar = primeBody->GetMass()*5;
    float maxThrust = (scalar*15);
    b2Vec2 difference = destination - primeBody->GetWorldCenter();
    difference *= scalar;
    if(difference.Length() > maxThrust){
        difference.Normalize();
        difference *= maxThrust;
    }
    primeBody->ApplyLinearImpulse(difference, b2Vec2(0,0), true);
}
void Nibbler::destructionEvent(){
	//end game some how
}
void Nibbler::startContact(Entity* other, float dmg){
	if(other->getHP() > hp){
	other->applyDmg(dmg);
	hp-=dmg;
	}else{
		energy += other->getEnergy();
	}
	 m_contacting++; 
}
void Nibbler::endContact(){ m_contacting--; }
