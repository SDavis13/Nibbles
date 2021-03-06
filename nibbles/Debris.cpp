#include "Debris.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#include <string>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

void Debris::initialize(int type, b2Vec2 initialVelocity){
	std::string name = "";
    b2FixtureDef fixDef;
    b2BodyDef bodDef;
    if(type == RANDOM)
        type = randDebrisType();
	switch(type){
	case DEBRIS1:
		/*name = "debris1";
        fixDef.density = 1;
        fixDef.friction = 0.4;
		hp = 0.1f;
        energy = 0.1;
		break;*/
    case DEBRIS3:
		/*name = "debris3";
        fixDef.density = 0.9;
        fixDef.friction = 0.45;
		hp = 0.1f;
        energy = 0.1;
		break;*/
	case DEBRIS2:
		name = "debris2";
        fixDef.density = 1.2;
        fixDef.friction = 0.3;
		hp = 0.1f;
        energy = 0.1;
		break;
	case CANISTER:
		name = "energycanister";
        fixDef.density = 0.2;
        fixDef.friction = 0.2;
		hp = 0.5f;
        energy = 2;
		break;
    default:
        name = "debris2";
        fixDef.density = 1;
		hp = 0.1;
        energy = 0.1;
        break;
	}
	m_contacting = 0;
    fixDef.restitution = 0.7;
    Part* debrisPart = new Part(*this, meshes[name], glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    bodDef.type = b2_dynamicBody;
    bodDef.position = b2Vec2(position.x, position.y);
    bodDef.angle = angle*M_PI/180;
    bodDef.linearVelocity = initialVelocity;
    std::vector<b2Shape*> shapes = debrisPart->computeShapes(false, 0);
    debrisPart->initialize(shapes, fixDef, bodDef);
    primeBody = debrisPart->body;
	primeBody->SetUserData((Entity*) this);
    mass = primeBody->GetMass();
    physValid = true;
    damage = false;
}
int Debris::randDebrisType(){
	srand(time(NULL));
	return (rand() % 3 + 1);
}
void Debris::behavior(){
    ++life;
    if(life > 50){
        damage = true;
    }
}
void Debris::destructionEvent(){
	//create smaller debris or destroy altogeher
}
void Debris::startContact(Entity* other, float dmg){
	hp-=dmg;
	m_contacting++;
}
void Debris::endContact(){ m_contacting--; }