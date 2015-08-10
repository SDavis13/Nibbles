#include "Bullet.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#include "Nibbler.hpp"

void Bullet::initialize(int type){
    std::string path = "";
    switch(type){
    case 0:
        path = "bullet.obj";
        break;
    case 1:
        path = "tearshot.obj";
        break;
    }
	hp = 0.1f;
	m_contacting = 0;
    Mesh bulletMesh(path.c_str());
    Part* bulletPart = new Part(*this, bulletMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(bulletPart);
	b2FixtureDef fixDef;
    b2BodyDef bodDef;
    bodDef.type = b2_dynamicBody;
    bodDef.fixedRotation = true;
	bodDef.linearVelocity = initialVelocity;
	bodDef.position = b2Vec2(position.x, position.z);
    std::vector<b2Shape*> shapes = bulletPart->computeShapes(true, 0);
    bulletPart->initialize(shapes, fixDef, bodDef);
    primeBody = bulletPart->body;
	primeBody->SetUserData((Entity*) this);
}
void Bullet::behavior(){
}