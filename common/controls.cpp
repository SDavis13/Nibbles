// Include GLEW
#include <glew/glew.h>

// Include GLFW
#include <glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

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

void computeMatricesFromInputs(){

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(glfwGetTime() - mylasttime);

    // Get mouse position
	double xpos, ypos;
    int xsize, ysize;
	glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &xsize, &ysize);

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
        viewDist =  temp + (pow((size-temp),curve))/(pow(period,(curve-1))) + player->MIN_SIZE;
    }
    float cameradistance = viewDist + zoom;

	int minDim;
	if(xsize > ysize){
		minDim = ysize;
	}else{
		minDim = xsize;
	}
    xpos -= xsize/2;//center at 0
    ypos -= ysize/2;
    xpos = size*xpos/minDim;//scale to GL coordinates
    ypos = size*ypos/minDim;

    player->applyThrust(b2Vec2(xpos,ypos));

	float FoV = myinitialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								player->getGLCenter() + glm::vec3(0,cameradistance,0), // Camera is here
								player->getGLCenter(), //focus destination
								glm::vec3(0,0,-1)      //up
						   );

	// For the next frame, the "last time" will be "now"
	mylasttime = currentTime;
}