// Include GLEW
#include <glew/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
using namespace glm;

#define _USE_MATH_DEFINES
#include <math.h>

#include "controls.hpp"
#include "nibbles\globals.hpp"
#include "nibbles\Nibbler.hpp"
#include "nibbles\Entity.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

// Initial Field of View
static float myinitialFoV = 45.0f;

static float zoom = 4;

static float myspeed = 10.0f;
static double mylasttime = 0;

static float period = 12; // can change this to whatever you want
static float curve = 4; //curve intensity; this can also be changed, but 4 seems good to me
static float size = -5;
static float viewDist = 0;

static unsigned int myTempVar = 0;

void computeMatricesFromInputs(){

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(glfwGetTime() - mylasttime);

    // Get mouse position
	double xpos, ypos;
    int xsize, ysize;
	glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &xsize, &ysize);

    if(xpos > 800){
        int examplethingamajig = 3;
    }

	// Zoom in
	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
		zoom -= deltaTime * myspeed;
	}
	// Zoom out
	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
		zoom += deltaTime * myspeed;
	}

    if(size != player->energy){
        size = player->energy;
        float temp = period*int(size/period);
        viewDist = ( temp + (pow((size-temp),curve))/(pow(period,(curve-1))) ) + player->MIN_SIZE*3;
    }
    float cameraDistance = viewDist + zoom;

	float FoV = myinitialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

    glm::vec3 cameraPos = /*player->getGLCenter() +*/ glm::vec3(0,0,cameraDistance);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								cameraPos, // Camera is here
								/*player->getGLCenter()*/glm::vec3(0), //focus destination
								glm::vec3(0,1,0)      //up
						   );

    xpos = -2*xpos/xsize + 1;//scale to GL coordinates
    ypos = 2*ypos/ysize - 1;
    glm::vec4 rayClip(xpos, ypos, -1.0, 1.0f);

    glm::vec4 rayEye = ProjectionMatrix._inverse() * rayClip;
    rayEye = glm::vec4 (rayEye.x, rayEye.y, -1.0f, 0.0f);

    glm::vec4 rayTemp = ViewMatrix._inverse() * rayEye;
    glm::vec3 rayWorld = glm::vec3(rayTemp.x, rayTemp.y, rayTemp.z);
    rayWorld = glm::normalize(rayWorld);

    float scalar = cameraDistance/rayTemp.z;
    b2Vec2 pointPosition(rayTemp.x*scalar, rayTemp.y*scalar);

    theLight->position = cameraPos;
    background->scale.x = cameraDistance;
    background->scale.y = cameraDistance;

    /*
    if(myTempVar%2048 == 0){
        printf("\n%f,%f",xpos,ypos);
        printf("\n%f,%f,%f", rayWorld.z, rayWorld.y, rayWorld.x);
    }else{
        ++myTempVar;
    }
    */

    player->applyThrust(pointPosition);

	// For the next frame, the "last time" will be "now"
	mylasttime = currentTime;
}