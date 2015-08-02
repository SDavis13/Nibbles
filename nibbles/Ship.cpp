#include "Ship.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#include "Nibbler.hpp"

void Ship::initialize(int type){
    Mesh shipMesh("coneship.obj");
    Part shipPart(*this, shipMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(shipPart);
}
void Ship::behavior(){
	
	b2Vec2 temp = player->getCenter();
	float distance = temp.dst(position);
	/*if(distance < field)
		//apply force in direction of nibbles
	else
		//apply force perpendicular to direction of nibbles
		//or
		//if(distance > outerRange)
			//pick direction and apply force
			//return
	//
	*/
}