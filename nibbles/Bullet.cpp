#include "Bullet.hpp"
#include "Mesh.hpp"
#include "Part.hpp"

void Bullet::initialize(int type){
    Mesh bulletMesh("bullet.obj");
    Part* bulletPart = new Part(*this, bulletMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(bulletPart);
}
void Nibbler::behavior(){

}