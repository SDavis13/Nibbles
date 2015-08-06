#include "Debris.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#include <string>
#include <time.h>
#include <cmath>

void Debris::initialize(int type){
	std::string path = "";
    b2FixtureDef fixDef;
    b2BodyDef bodDef;
    if(type == RANDOM)
        type = randDebrisType();
	switch(type){
	case DEBRIS1:
		path = "debris1.obj";
        fixDef.density = 
        energy = 0.1;
		break;
	case DEBRIS2:
		path = "debris2.obj";
        energy = 0.1;
		break;
	case DEBRIS3:
		path = "debris3.obj";
        energy = 0.1;
		break;
	case CANISTER:
		path = "energycanister.obj";
        energy = 2;
		break;
    default:
        path = "debris1.obj";
        energy = 0.1;
        break;
	}
    Mesh debrisMesh(path.c_str());
    Part* debrisPart = new Part(*this, debrisMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(debrisPart);
	
    bodDef.type = b2_dynamicBody;
    std::vector<b2Shape*> shapes = debrisPart->computeShapes(false, 0);
    debrisPart->initialize(shapes, fixDef, bodDef);
    primeBody = debrisPart->body;
}
int Debris::randDebrisType(){
	srand(time(NULL));
	return (rand() % 3 + 1);
}
void behavior(){}