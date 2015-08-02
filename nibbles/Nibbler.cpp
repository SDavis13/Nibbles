#include "Nibbler.hpp"
#include "Mesh.hpp"
#include "Part.hpp"

void Nibbler::initialize(int type){
    Mesh nibblerMesh("nibblercore.obj");
    Part nibblerPart(*this, nibblerMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(nibblerPart);
}
void Nibbler::behavior(){
}