#pragma once
#ifndef LIGHTSOURCE_HPP
#define LIGHTSOURCE_HPP

#include "globals.hpp"
#include "Entity.hpp"
#include "Part.hpp"

class LightSource : public Part{
public:
    glm::vec3 lightPos;
    glm::vec3 lightColor;
    LightSource(Entity& source, Mesh& mesh, glm::vec3 position, glm::vec3 rotationAxis, float angle, glm::vec3 scale, glm::vec3 lightpos) 
            : Part(source, mesh, position, rotationAxis, angle, scale), lightPos(lightpos), lightColor(1) {}
    LightSource() : Part(), lightPos(0), lightColor(1) {}
    void setUpLight();
};

#endif