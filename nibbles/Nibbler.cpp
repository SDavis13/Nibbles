#include "Nibbler.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/Joints/b2RopeJoint.h>

void Nibbler::initialize(int type, b2Vec2 initialVelocity){
    Part* core = new Part(*this, meshes["nibblercore"], glm::vec3(0), glm::vec3(0,0,1), 0, glm::vec3(MIN_SIZE));
    Part* corona = new Part(*this, meshes["nibblercorona"], glm::vec3(0), glm::vec3(0,0,1), 0, glm::vec3(MIN_SIZE));
    //Part* core2 = new Part(*this, meshes["nibblercore"], glm::vec3(0), glm::vec3(0,0,1), 0, glm::vec3((float)MIN_SIZE*2/3));
    //Part* corona2 = new Part(*this, meshes["nibblercorona"], glm::vec3(0), glm::vec3(0,0,1), 0, glm::vec3((float)MIN_SIZE*2/3));
    //Part* core3 = new Part(*this, meshes["nibblercore"], glm::vec3(0), glm::vec3(0,0,1), 0, glm::vec3((float)MIN_SIZE/3));
    //Part* corona3 = new Part(*this, meshes["nibblercorona"], glm::vec3(0), glm::vec3(0,0,1), 0, glm::vec3((float)MIN_SIZE/3));
    corona->opacity = 0.4;
    //corona2->opacity = 0.4;
    //corona3->opacity = 0.4;
    b2FixtureDef fixDef;
    fixDef.density = 10;
    b2BodyDef bodDef;
    bodDef.type = b2_dynamicBody;
    bodDef.position = b2Vec2(position.x, position.y);
    bodDef.fixedRotation = true;
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
    b2Vec2 difference = primeBody->GetPosition() - objLoc;
    float distanceSqr = difference.LengthSquared();
    float force = mass*objMass/distanceSqr * 100000;
    difference.Normalize();
    difference *= force;
    return difference;
}
void Nibbler::behavior(){
    /*unsigned int i = 0;
    unsigned int listSize = parts.size();
    while(i < listSize){
        Part* curPart = parts[i];
        if(i > 1){
            glm::vec3& partPos = (curPart->position);
            if(i%2 == 0){
                
            }else{
                partPos = parts[i-1]->position;
            }
        }
        if(!(curPart->physValid)){
            curPart->angle += 5.3;
            if(curPart->angle > 360){
                curPart->angle -= 360;
            }
        }
        ++i;
    }*/
}
void Nibbler::applyThrust(b2Vec2 destination){
    float scalar = primeBody->GetMass()*5;
    float maxThrust = (scalar*15);
    b2Vec2 difference = destination - primeBody->GetPosition();
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
