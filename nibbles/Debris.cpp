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
    if(type == 0)
        type = randDebrisType();
	switch(type){
	case 1:
		path = "debris1.obj";
		break;
	case 2:
		path = "debris2.obj";
		break;
	case 3:
		path = "debris3.obj";
		break;
	case 4:
		path = "energycanister.obj";
		break;
    default:
        path = "debris1.obj";
        break;
	}
    Mesh debrisMesh(path.c_str());
    Part* debrisPart = new Part(*this, debrisMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(debrisPart);
	
    bodDef.type = b2_dynamicBody;
    bodDef.fixedRotation = true;
    std::vector<b2Shape*> shapes = debrisPart->computeShapes(true, 0);
    debrisPart->initialize(shapes, fixDef, bodDef);
    primeBody = debrisPart->body;
}
int Debris::randDebrisType(){
	srand(time(NULL));
	return (rand() % 3 + 1);
}
void behavior(){}