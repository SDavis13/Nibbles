#include "Bullet.hpp"
#include "Mesh.hpp"
#include "Part.hpp"

void Bullet::initialize(int type){
    Mesh bulletMesh("bullet.obj");
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
}
void Bullet::behavior(){

}