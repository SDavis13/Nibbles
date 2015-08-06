#include "Debris.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#include <string>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

void Debris::initialize(int type){
	std::string path = "";
    b2FixtureDef fixDef;
    b2BodyDef bodDef;
    if(type == RANDOM)
        type = randDebrisType();
	switch(type){
	case DEBRIS1:
		path = "debris1.obj";
        fixDef.density = 1;
        fixDef.friction = 0.4;
        energy = 0.1;
		break;
	case DEBRIS2:
		path = "debris2.obj";
        fixDef.density = 1.2;
        fixDef.friction = 0.3;
        energy = 0.1;
		break;
	case DEBRIS3:
		path = "debris3.obj";
        fixDef.density = 0.9;
        fixDef.friction = 0.45;
        energy = 0.1;
		break;
	case CANISTER:
		path = "energycanister.obj";
        fixDef.density = 0.2;
        fixDef.friction = 0.2;
        energy = 2;
		break;
    default:
        path = "debris1.obj";
        fixDef.density = 1;
        energy = 0.1;
        break;
	}
    fixDef.restitution = 0.7;
    Mesh debrisMesh(path.c_str());
    Part* debrisPart = new Part(*this, debrisMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(debrisPart);
    bodDef.type = b2_dynamicBody;
    bodDef.position = b2Vec2(position.x, position.z);
    bodDef.angle = angle*M_PI/180;
    std::vector<b2Shape*> shapes = debrisPart->computeShapes(false, 0);
    debrisPart->initialize(shapes, fixDef, bodDef);
    primeBody = debrisPart->body;
    mass = primeBody->GetMass();
}
int Debris::randDebrisType(){
	srand(time(NULL));
	return (rand() % 3 + 1);
}
void Debris::behavior(){}