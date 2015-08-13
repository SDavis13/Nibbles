#include "Ship.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#include "Nibbler.hpp"
#include "Debris.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

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
        maxThrust = 200*scale.x*scale.y;
        bulletType = BULLET;
        break;
    case DRONE:
    default: //DRONE
        shipMesh = &meshes["drone"];
        hp = 20.0f;
        fixDef.density = 7;
        fixDef.friction = 0.2;
        energy = 7;
        maxThrust = 400*scale.x*scale.y;
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
    bodDef.angle = angle*M_PI/180;
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
	float desiredAngle = (float)std::atan2(temp.x, temp.y);
	temp.Normalize();
	float field = FIELDSCALE;
		field*= (player->getGravity(primeBody->GetMass(), temp)).Length();
	if(distance < field){
		//apply force in direction of nibbles
		temp.x*=maxThrust;
		temp.y*=maxThrust;
	}else{
			float desiredAngle = (float)std::atan2(temp.y, temp.x);
			float holder = temp.x;
			temp.x = temp.y*maxThrust;
			temp.y = holder*maxThrust;		
	}
	primeBody->SetTransform( primeBody->GetPosition(), desiredAngle );
	primeBody->ApplyLinearImpulse(temp, primeBody->GetLocalCenter(), true);
}
static glm::vec3 randomDebrisPos(Ship& ship){
    glm::vec3 debrisPos(ship.primeBody->GetWorldCenter().x, ship.primeBody->GetWorldCenter().y, 0);
    debrisPos.x += ((float)(std::rand() % 1024) - 512)/8192 * ship.scale.x;
    debrisPos.y += ((float)(std::rand() % 1024) - 512)/8192 * ship.scale.y;
    return debrisPos;
}
void Ship::destructionEvent(){
    float debrisScale = scale.x * (bulletType + 1) / 4;
    Debris* debris1 = new Debris(randomDebrisPos(*this), glm::vec3(0,0,1), (rand() % 360), glm::vec3(debrisScale));
    debris1->initialize(2, b2Vec2(0,0));
    Debris* debris2 = new Debris(randomDebrisPos(*this), glm::vec3(0,0,1), (rand() % 360), glm::vec3(debrisScale));
    debris2->initialize(2, b2Vec2(0,0));
    Debris* debris3 = new Debris(randomDebrisPos(*this), glm::vec3(0,0,1), (rand() % 360), glm::vec3(debrisScale));
    debris3->initialize(2, b2Vec2(0,0));
    Debris* canister1 = new Debris(randomDebrisPos(*this), glm::vec3(0,0,1), (rand() % 360), glm::vec3(debrisScale));
    canister1->initialize(4, b2Vec2(0,0));
    Debris* canister2 = new Debris(randomDebrisPos(*this), glm::vec3(0,0,1), (rand() % 360), glm::vec3(debrisScale));
    canister2->initialize(4, b2Vec2(0,0));
    gameMaster->addEntity(debris1);
    gameMaster->addEntity(debris2);
    gameMaster->addEntity(debris3);
    gameMaster->addEntity(canister1);
    gameMaster->addEntity(canister2);
}
void Ship::fire(){
    glm::vec3 bulletPos(primeBody->GetWorldCenter().x, primeBody->GetWorldCenter().y, 0);
    float bulletScale = scale.x * (bulletType + 1) / 4;
    Bullet* newBullet = new Bullet(bulletPos, glm::vec3(0,0,1), angle, glm::vec3(bulletScale));
    b2Vec2 bulletVelocity(cos(primeBody->GetAngle()), sin(primeBody->GetAngle()));
    bulletVelocity *= 12;
    bulletVelocity += primeBody->GetLinearVelocity();
    newBullet->initialize(bulletType, bulletVelocity);
}
void Ship::startContact(Entity* other, float dmg){
	hp-=dmg;
	m_contacting++;
}
void Ship::endContact(){ m_contacting--;}