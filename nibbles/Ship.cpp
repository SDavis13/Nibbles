#include "Ship.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#include "Nibbler.hpp"
#include "Debris.hpp"

void Ship::initialize(int type, b2Vec2 initialVelocity){
    Mesh* shipMesh;
    b2FixtureDef fixDef;
    switch(type){
    case CONESHIP:
        shipMesh = &meshes["coneship"];
		hp = 50.0f;
        fixDef.density = 5;
        fixDef.friction = 0.3;
        energy = 5;
        maxThrust = 500*scale.x;
        bulletType = BULLET;
        break;
    case DRONE:
    default: //DRONE
        shipMesh = &meshes["drone"];
        hp = 20.0f;
        fixDef.density = 7;
        fixDef.friction = 0.2;
        energy = 7;
        maxThrust = 400*scale.x;
        bulletType = TEARSHOT;
        break;
	}
	m_contacting = 0;
    fixDef.restitution = 0.55;
	Part* shipPart = new Part(*this, *shipMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
	b2BodyDef bodDef;
	bodDef.type = b2_dynamicBody;
    bodDef.position = b2Vec2(position.x, position.y);
	bodDef.fixedRotation = false;
    bodDef.linearVelocity = initialVelocity;
	std::vector<b2Shape*> shapes = shipPart->computeShapes(false, 0);
	shipPart->initialize(shapes, fixDef, bodDef);
	primeBody = shipPart->body;
	primeBody->SetUserData((Entity*) this);
    mass = primeBody->GetMass();
    physValid = true;
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
	primeBody->ApplyForceToCenter(temp, true);
}
void Ship::destructionEvent(){
	
}
void Ship::fire(){

}
void Ship::startContact(Entity* other, float dmg){
	other->applyDmg(dmg);
	hp-=dmg;
	m_contacting++;
}
void Ship::endContact(){ m_contacting--;}