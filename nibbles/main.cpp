// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
//GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/controls.hpp>

#include "globals.hpp"
#include "Entity.hpp"
#include "Part.hpp"
#include "Mesh.hpp"
#include "LightSource.hpp"
#include "Nibbler.hpp"
#include "Debris.hpp"

//#define CRTDBG_MAP_ALLOC
//#include <crtdbg.h>

int main( void )
{
    int temp = initializeOGLstuff();
    if( temp != 0){
        return temp;
    }

    Nibbler* nibbles = player;
    Ship* another = new Ship(glm::vec3(10,10,0), glm::vec3(0,0,1), 0, glm::vec3(1));
    Ship* another2 = new Ship(glm::vec3(-10,10,0), glm::vec3(0,0,1), 0, glm::vec3(0.5));
    Ship* fighter = new Ship(glm::vec3(-10,-10,0), glm::vec3(0,0,1), 0, glm::vec3(0.5));
    Ship* drone = new Ship(glm::vec3(10,-10,0), glm::vec3(0,0,1), 0, glm::vec3(0.2));
    Debris* debris = new Debris(glm::vec3(0,-15,0), glm::vec3(0,0,1), 0, glm::vec3(0.4));
    Debris* canister = new Debris(glm::vec3(-15,0,0), glm::vec3(0,0,1), 0, glm::vec3(0.1));

    Ship* onemore1 = new Ship(glm::vec3(15,0,0), glm::vec3(0,0,1), 0, glm::vec3(0.3));
    Ship* onemore2 = new Ship(glm::vec3(0,15,0), glm::vec3(0,0,1), 0, glm::vec3(0.1));
    Debris* onemore3 = new Debris(glm::vec3(-17,-17,0), glm::vec3(0,0,1), 0, glm::vec3(1));
    Debris* onemore4 = new Debris(glm::vec3(17,-17,0), glm::vec3(0,0,1), 0, glm::vec3(2));
    Debris* onemore5 = new Debris(glm::vec3(-17,17,0), glm::vec3(0,0,1), 0, glm::vec3(3));
    Debris* onemore6 = new Debris(glm::vec3(17,17,0), glm::vec3(0,0,1), 0, glm::vec3(0.7));

    nibbles->initialize(0, b2Vec2(0,0));
    another->initialize(0, b2Vec2(0,0));
    another2->initialize(1, b2Vec2(0,0));
    fighter->initialize(0, b2Vec2(0,0));
    drone->initialize(1, b2Vec2(0,0));
    debris->initialize(2, b2Vec2(0,0));
    canister->initialize(4, b2Vec2(0,0));
    onemore1->initialize(0, b2Vec2(0,0));
    onemore2->initialize(1, b2Vec2(0,0));
    onemore3->initialize(0, b2Vec2(0,0));
    onemore4->initialize(0, b2Vec2(0,0));
    onemore5->initialize(0, b2Vec2(0,0));
    onemore6->initialize(0, b2Vec2(0,0));

    gameMaster->addEntity(another);
    gameMaster->addEntity(another2);
    gameMaster->addEntity(fighter);
    gameMaster->addEntity(drone);
    gameMaster->addEntity(debris);
    gameMaster->addEntity(canister);
    gameMaster->addEntity(onemore1);
    gameMaster->addEntity(onemore2);
    gameMaster->addEntity(onemore3);
    gameMaster->addEntity(onemore4);
    gameMaster->addEntity(onemore5);
    gameMaster->addEntity(onemore6);

	// Load it into a VBO

	//GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	//GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	//GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	//GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

	// For speed computation
	double lastPrint = glfwGetTime();
    double currentTime;
	int nbFrames = 0;
    int framenumber = 0;

    double lastTime = glfwGetTime();

    int velocityIterations = 0;
    int positionIterations = 0;

	do{

        ++framenumber;
		// Measure speed
		currentTime = glfwGetTime();
		nbFrames++;
		if ( currentTime - lastPrint >= 1.0 ){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0/double(nbFrames));
			nbFrames = 0;
			lastPrint += 1.0;
            //printf("%f,%f,%f\n",sunandmoon.lightColor.r,sunandmoon.lightColor.g,sunandmoon.lightColor.b);
		}
        universe->Step((currentTime-lastTime)/1000, 6, 3);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		projectionMatrix = getProjectionMatrix();
		viewMatrix = getViewMatrix();
		
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
		
		// Use our shader
		glUseProgram(programID);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			vertexPosition_modelspaceID, // The attribute we want to configure
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(vertexUVID);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			vertexUVID,                       // The attribute we want to configure
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(vertexNormal_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			vertexNormal_modelspaceID,        // The attribute we want to configure
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

        light->setUpLight();

        gameMaster->update();
        gameMaster->render();

        /*for(unsigned int i = 0; i < entities.size(); ++i){
            entities[i]->update();
            entities[i]->render();
        }

        b2Body* bodies = universe->GetBodyList();
        while(bodies != NULL){
            if(bodies != player->primeBody){
                bodies->ApplyForceToCenter( ( player->getGravity(bodies->GetMass(), bodies->GetPosition()) ), true);
            }
            bodies = bodies->GetNext();
        }*/

        if(framenumber%1024 == 0){
            framenumber--;
            framenumber++;
        }

		glDisableVertexAttribArray(vertexPosition_modelspaceID);
		glDisableVertexAttribArray(vertexUVID);
		glDisableVertexAttribArray(vertexNormal_modelspaceID);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

        lastTime = currentTime;

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
    //_CrtDumpMemoryLeaks();

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &Texture);
    
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}