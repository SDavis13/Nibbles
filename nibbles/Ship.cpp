#include "Ship.hpp"
#include "Mesh.hpp"
#include "Part.hpp"

void Ship::initialize(int type){
    Mesh shipMesh("coneship.obj");
    Part shipPart(*this, shipMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(shipPart);
}