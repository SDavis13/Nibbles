#include "Bullet.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#include "Nibbler.hpp"

void Bullet::initialize(int type, b2Vec2 initialVelocity){
    std::string name = "";
    switch(type){
    case 0:
        name = "bullet";
        break;
    case 1:
        name = "tearshot";
        break;
    }
	hp = 0.1f;
	m_contacting = 0;
    Part* bulletPart = new Part(*this, meshes[name], glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(bulletPart);
	b2FixtureDef fixDef;
    b2BodyDef bodDef;
    bodDef.type = b2_dynamicBody;
    bodDef.fixedRotation = true;
	bodDef.linearVelocity = initialVelocity;
	bodDef.position = b2Vec2(position.x, position.y);
    std::vector<b2Shape*> shapes = bulletPart->computeShapes(true, 0);
    bulletPart->initialize(shapes, fixDef, bodDef);
    primeBody = bulletPart->body;
	primeBody->SetUserData((Entity*) this);
}
void Bullet::behavior(){}
void Bullet::destructionEvent(){
	//pretty much nothing, shower of sparks?
}
void Bullet::startContact(Entity* other, float dmg){
	other->applyDmg(dmg);
	hp-=hp;
	m_contacting++;
}
void Bullet::endContact(){ m_contacting--;}