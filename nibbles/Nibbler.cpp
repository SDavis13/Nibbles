#include "Nibbler.hpp"
#include "Mesh.hpp"
#include "Part.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2Body.h>

void Nibbler::initialize(int type){
    Mesh nibblerMesh("nibblercore.obj");
    Part* nibblerPart = new Part(*this, nibblerMesh, glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    parts.push_back(nibblerPart);
    b2FixtureDef fixDef;
    b2BodyDef bodDef;
    bodDef.type = b2_dynamicBody;
    bodDef.fixedRotation = true;
    bodDef.position = b2Vec2(position.x, position.z);
    bodDef.angle = angle*M_PI/180;
    std::vector<b2Shape*> shapes = nibblerPart->computeShapes(true, 0);
    nibblerPart->initialize(shapes, fixDef, bodDef);
    primeBody = nibblerPart->body;
    mass = primeBody->GetMass();
    energy = MIN_SIZE;
    physValid = true;
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