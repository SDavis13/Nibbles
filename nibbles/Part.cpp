#define PART_CPP

#include "Part.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include <Box2D/Collision/Shapes/b2CircleShape.h>

void Part::generateTransform(glm::mat4& transform) const{
    assert(valid);

    transform = glm::translate(transform, whole.position);
    transform = glm::rotate(transform, whole.angle, whole.rotationAxis);
    transform = glm::scale(transform, whole.scale);
    
    transform = glm::translate(transform, position);
    transform = glm::rotate(transform, angle, rotationAxis);
	transform = glm::scale(transform, scale);
}

glm::mat4 Part::generateTransform() const{
    glm::mat4 returnValue = glm::mat4(1.0);
    generateTransform(returnValue);
    return returnValue;
}

void Part::render(glm::mat4& model) const{
	mvp = projectionMatrix * viewMatrix * model;

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &model[0][0]);

    // Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glDrawElements(
		GL_TRIANGLES,      // mode
		mesh.numindices,    // count
		GL_UNSIGNED_SHORT,   // type
		(void*)(sizeof(unsigned short) * mesh.startindex)  // element array buffer offset
	);
}

void Part::render() const{
    render(generateTransform());
}

std::vector<b2Shape*> Part::computeShapes(bool circular, float offset){
    std::vector<b2Shape*> shapes;
    if(circular){
        b2CircleShape* shape = new b2CircleShape();
        shape->m_radius = mesh.getRadius() + offset;
        shapes.push_back(shape);
    }else{
        std::vector<std::vector<b2Vec2> > vertices = mesh.getHullPoly();
        if(!(scale.x == 0 && scale.z == 0)){
            for(int i = 0; i < vertices.size(); ++i){
                for(int j = 0; j < vertices[i].size(); ++j){
                    (vertices[i])[j].x *= scale.x;
                    (vertices[i])[j].y *= scale.z;
                }
            }
        }

        for(int i = 0; i < vertices.size(); ++i){
            b2PolygonShape* myShape = new b2PolygonShape;
            myShape->Set(&(vertices[i]).front(), (vertices[i]).size() );
            shapes.push_back(myShape);
        }
    }
    return shapes;
}

void Part::initialize(std::vector<b2Shape*>& shapes, b2FixtureDef fixDefinition, b2BodyDef bodyDefinition){
    body = universe->CreateBody(&bodyDefinition);
    for(int i = 0; i < shapes.size(); i++){
        fixDefinition.shape = shapes[i];
        body->CreateFixture(&fixDefinition);
    }
    physValid = true;
}