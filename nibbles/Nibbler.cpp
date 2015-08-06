#include "Nibbler.hpp"
#include "Mesh.hpp"
#include "Part.hpp"

void Nibbler::initialize(int type){
    Mesh nibblerMesh("nibblercore.obj");
    Part* nibblerPart = new Part(*this, nibblerMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(nibblerPart);
}
b2Vec2 Nibbler::getGravity(float objMass, b2Vec2 objLoc){
    b2Vec2 difference = primeBody->GetWorldCenter() - objLoc;
    float distanceSqr = difference.LengthSquared();
    float force = mass*objMass/distanceSqr;
    difference.Normalize();
    difference *= force;
    return difference;
}
void Nibbler::behavior(){
}
void Nibbler::applyThrust(b2Vec2 destination){
    b2Vec2 difference = destination - primeBody->GetWorldCenter();
    if(difference.Length() > MAX_THRUST){
        difference.Normalize();
        difference *= MAX_THRUST;
    }
    primeBody->ApplyForceToCenter(difference, true);
}