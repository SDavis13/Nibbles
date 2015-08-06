#include "Ship.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#include "Nibbler.hpp"

void Ship::initialize(int type){
    Mesh shipMesh;
    switch(type){
    case CONESHIP:
        shipMesh = Mesh("coneship.obj");
        break;
    case DRONE:
        shipMesh = Mesh("drone1.obj");
        break;
    default: //DRONE
        shipMesh = Mesh("drone1.obj");
        break;
    }
    
    Part* shipPart = new Part(*this, shipMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(shipPart);
}
void Ship::behavior(){
	b2Vec2 temp = getWorldCenter()-player->getWorldCenter();
	float distance = temp.Length();
	temp.Normalize();
	float field = FIELDSCALE*(player->getGravity(primeBody->GetMass(), temp)).Length();
	if(distance < field){
		//apply force in direction of nibbles
		temp.x*=-maxThrust;
		temp.y*=-maxThrust;
	}
	else{
		if(distance > field *3){
		//pick direction and apply force
		temp.x*=maxThrust;
		temp.y*=maxThrust;
		}else{
		float holder = temp.x;
		temp.x = temp.y*maxThrust;
		temp.y = holder*maxThrust;
		}
	}
	//
	primeBody->ApplyForceToCenter(temp, true);
}