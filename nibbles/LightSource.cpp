#include "LightSource.hpp"

void LightSource::setUpLight(){
    glm::mat4 transform = generateTransform();
    glUniformMatrix4fv(LightMatrixID, 1, GL_FALSE, &transform[0][0]);
    glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(LightColorID, lightColor.r, lightColor.g, lightColor.b);
}