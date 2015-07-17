#define PART_CPP

#include "Part.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

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

void Part::render() const{
    render(generateTransform());
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
