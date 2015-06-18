// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>//mine added from tutorial04
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>

#include <Box2d/Dynamics/b2Body.h>

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


	// Open a window and create its OpenGL context
	//window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);//original
	window = glfwCreateWindow( 640, 640, "Lab 01 - Two Triangles", NULL, NULL);//mine
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "VertexShader.vertexshader", "FragmentShader.fragmentshader" );

	// Get a handle for our "MVP" uniform //mine added from tutorial04
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Get a handle for our buffers
	GLuint vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
	GLuint vertexColorID = glGetAttribLocation(programID, "vertexColor");//mine copied from tutorial04
	GLuint vertexUVID = glGetAttribLocation(programID, "vertexUV");//mine copied from tutorial05

	//mine added from tutorial04 -v, also changed
	// Projection matrix : 45� Field of View, 1:1 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
	// Camera matrix
	/*glm::mat4 View       = glm::lookAt(//original
								glm::vec3(0,0,10), // Camera is at (0,0,10), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );*/
	//mine -v
	glm::vec3 cameraPos   = glm::vec3(0.0f,0.0f,10.0f); // Camera is at (0,0,10), in World Space
	glm::vec3 cameraFocus = glm::vec3(0.0f,0.0f,0.0f); // and looks at the origin
	glm::vec3 cameraHead  = glm::vec3(0.0f,1.0f,0.0f); // Head is up (set to 0,-1,0 to look upside-down)
	glm::mat4 View        = glm::lookAt(cameraPos,cameraFocus,cameraHead);
	//mine -^
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around
	//mine added from tutorial04 -^

	// Load the texture using any two methods //mine added from tutorial05
	GLuint Texture = loadBMP_custom("star.bmp", false);
	//GLuint Texture = loadDDS("star2.dds");

	// Get a handle for our "myTextureSampler" uniform //mine added from tutorial05
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	/*
	static const GLfloat g_vertex_buffer_data[] = { //original
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};
	*/
	static GLfloat g_vertex_buffer_data[] = { //mine
		//Top Right triangle
		 0.0f,  0.0f,   0.0f,//left
		 4.0f,  0.0f,   0.0f,//right
		 2.0f,  3.464f, 0.0f,//vertical
		//Bottom Right triangle
		 0.0f,  0.0f,   0.0f,//left
		 4.0f,  0.0f,   0.0f,//right
		 2.0f, -3.464f, 0.0f,//vertical

		//Bottom triangle
		-2.0f, -3.464f, 0.0f,//left
		 2.0f, -3.464f, 0.0f,//right
		 0.0f,  0.0f,   0.0f,//vertical

		//Bottom Left triangle
		-4.0f,  0.0f,   0.0f,//left
		 0.0f,  0.0f,   0.0f,//right
		-2.0f, -3.464f, 0.0f,//vertical
		//Top Left triangle
		-4.0f,  0.0f,   0.0f,//left
		 0.0f,  0.0f,   0.0f,//right
		-2.0f,  3.464f, 0.0f,//vertical

		//Top triangle
		-2.0f,  3.464f, 0.0f,//left
		 2.0f,  3.464f, 0.0f,//right
		 0.0f,  0.0f,   0.0f,//vertical

		//Middle triangle
		-1.0f, -0.577f, 0.0f,//left
		 1.0f, -0.577f, 0.0f,//right
		 0.0f,  1.155f, 0.0f,//vertical

		//Middle triangle 2
		-1.0f,  0.577f, 0.0f,//left
		 1.0f,  0.577f, 0.0f,//right
		 0.0f, -1.155f, 0.0f,//vertical
	};

	static GLfloat g_color_buffer_data[] = { //mine
		//Top Right triangle
		 1.0f,  1.0f, 1.0f,//left - middle
		 1.0f,  0.0f, 0.0f,//right - clockwise - red
		 1.0f,  0.0f, 1.0f,//vertical - counterClockwise - magenta
		//Bottom Right triangle
		 1.0f,  1.0f, 1.0f,//left - middle
		 1.0f,  0.0f, 0.0f,//right - counterClockwise - red
		 1.0f,  1.0f, 0.0f,//vertical - clockwise - yellow

		//Bottom triangle
		 0.0f,  1.0f, 0.0f,//left - clockwise - green
		 1.0f,  1.0f, 0.0f,//right - counterClockwise - yellow
		 1.0f,  1.0f, 1.0f,//vertical - middle

		//Bottom Left triangle
		 0.0f,  1.0f, 1.0f,//left - clockwise - cyan
		 1.0f,  1.0f, 1.0f,//right - middle
		 0.0f,  1.0f, 0.0f,//vertical - counterClockwise - green
		//Top Left triangle
		 0.0f,  1.0f, 1.0f,//left - counterClockwise - cyan
		 1.0f,  1.0f, 1.0f,//right - middle
		 0.0f,  0.0f, 1.0f,//vertical - clockwise - blue
		
		//Top triangle
		 0.0f,  0.0f, 1.0f,//left - counterClockwise - blue
		 1.0f,  0.0f, 1.0f,//right - clockwise - magenta
		 1.0f,  1.0f, 1.0f,//vertical - middle

		//Middle triangle
		 1.0f,  1.0f, 1.0f,//left
		 1.0f,  1.0f, 1.0f,//right
		 1.0f,  1.0f, 1.0f,//vertical

		//Middle triangle 2
		 1.0f,  1.0f, 1.0f,//left
		 1.0f,  1.0f, 1.0f,//right
		 1.0f,  1.0f, 1.0f,//vertical
	};

	static GLfloat g_uv_buffer_data[] = { //mine
		//Top Right triangle
		 0.5f,  0.5f,   //left
		 1.077f,  0.5f,   //right
		 0.789f,  1.0f, //vertical
		//Bottom Right triangle
		 0.5f,  0.5f,   //left
		 1.077f,  0.5f,   //right
		 0.789f,  0.0f, //vertical

		//Bottom triangle
		 0.211f,  0.0f, //left
		 0.789f,  0.0f, //right
		 0.5f,  0.5f,   //vertical

		//Bottom Left triangle
		-0.077,  0.5f,   //left
		 0.5f,  0.5f,   //right
		 0.211f,  0.0f, //vertical
		//Top Left triangle
		-0.077,  0.5f,   //left
		 0.5f,  0.5f,   //right
		 0.211f,  1.0f, //vertical

		//Top triangle
		 0.211f,  1.0f, //left
		 0.789f,  1.0f, //right
		 0.5f,  0.5f,   //vertical

		//Middle triangle
		 0.356f,  0.417f, //left
		 0.644f,  0.417f, //right
		 0.5f,  0.667f, //vertical

		//Middle triangle 2
		 0.356f,  0.583f, //left
		 0.644f,  0.583f, //right
		 0.5f,  0.333f, //vertical
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint colorbuffer;//mine added (copied from tutorial04)
	glGenBuffers(1, &colorbuffer);//mine added (copied from tutorial04)
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);//mine added (copied from tutorial04)
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);//mine added (copied from tutorial04)

	GLuint uvbuffer;//mine added (copied from tutorial05)
	glGenBuffers(1, &uvbuffer);//mine added (copied from tutorial05)
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);//mine added (copied from tutorial05)
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);//mine added (copied from tutorial05)

	//color rotation variables //mine
	int frameCount = 0;
	int index = 1;
	int speed = 512;
	float incrementAmount = 1/((float)speed);

	do{
		glm::mat4 MVP        = Projection * View * Model;//mine
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);

		// mine added from tutorial04
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0 //mine-v added from tutorial05
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);//mine-^

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);//mine
		glVertexAttribPointer(
			vertexPosition_modelspaceID, // The attribute we want to configure
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors (Mine Copied from tutorial04)
		glEnableVertexAttribArray(vertexColorID);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);//mine
		glVertexAttribPointer(
			vertexColorID,               // The attribute we want to configure
			3,                           // size
			GL_FLOAT,                    // type
			GL_FALSE,                    // normalized?
			0,                           // stride
			(void*)0                     // array buffer offset
		);

		// 2nd attribute buffer : UVs //mine added from tutorial05
		glEnableVertexAttribArray(vertexUVID);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			vertexUVID,                   // The attribute we want to configure
			2,                            // size : U+V => 2
			GL_FLOAT,                     // type
			GL_FALSE,                     // normalized?
			0,                            // stride
			(void*)0                      // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 24); // 24 indices starting at 0 -> 8 triangles //mine changed, used to be one triangle

		glDisableVertexAttribArray(vertexPosition_modelspaceID);
		glDisableVertexAttribArray(vertexColorID);//mine added from tutorial04
		glDisableVertexAttribArray(vertexUVID);//mine added from tutorial05

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		//color rotation //mine from here through the end of the loop
		g_color_buffer_data[3  + ((2*index - 1)%3)] += ((index)%2)*incrementAmount;//top right
		g_color_buffer_data[3  + ((2*index - 1)%3)] -= ((index-1)%2)*incrementAmount;//clockwise
		g_color_buffer_data[6  + ((2*index    )%3)] += ((index-1)%2)*incrementAmount;//top right
		g_color_buffer_data[6  + ((2*index    )%3)] -= ((index)%2)*incrementAmount;//counterclockwise

		g_color_buffer_data[12 + ((2*index - 1)%3)] += ((index)%2)*incrementAmount;//bottom right
		g_color_buffer_data[12 + ((2*index - 1)%3)] -= ((index-1)%2)*incrementAmount;//counterclockwise
		g_color_buffer_data[15 + ((2*index + 1)%3)] += ((index-1)%2)*incrementAmount;//bottom right
		g_color_buffer_data[15 + ((2*index + 1)%3)] -= ((index)%2)*incrementAmount;//clockwise

		g_color_buffer_data[18 + ((2*index    )%3)] += ((index)%2)*incrementAmount;//bottom
		g_color_buffer_data[18 + ((2*index    )%3)] -= ((index-1)%2)*incrementAmount;//clockwise
		g_color_buffer_data[21 + ((2*index + 1)%3)] += ((index-1)%2)*incrementAmount;//bottom
		g_color_buffer_data[21 + ((2*index + 1)%3)] -= ((index)%2)*incrementAmount;//counterclockwise

		g_color_buffer_data[27 + ((2*index - 1)%3)] += ((index-1)%2)*incrementAmount;//bottom left
		g_color_buffer_data[27 + ((2*index - 1)%3)] -= ((index)%2)*incrementAmount;//clockwise
		g_color_buffer_data[33 + ((2*index    )%3)] += ((index)%2)*incrementAmount;//bottom left
		g_color_buffer_data[33 + ((2*index    )%3)] -= ((index-1)%2)*incrementAmount;//counterclockwise

		g_color_buffer_data[36 + ((2*index - 1)%3)] += ((index-1)%2)*incrementAmount;//top left
		g_color_buffer_data[36 + ((2*index - 1)%3)] -= ((index)%2)*incrementAmount;//counterclockwise
		g_color_buffer_data[42 + ((2*index + 1)%3)] += ((index)%2)*incrementAmount;//top left
		g_color_buffer_data[42 + ((2*index + 1)%3)] -= ((index-1)%2)*incrementAmount;//clockwise

		g_color_buffer_data[45 + ((2*index + 1)%3)] += ((index)%2)*incrementAmount;//top
		g_color_buffer_data[45 + ((2*index + 1)%3)] -= ((index-1)%2)*incrementAmount;//counterclockwise
		g_color_buffer_data[48 + ((2*index    )%3)] += ((index-1)%2)*incrementAmount;//top
		g_color_buffer_data[48 + ((2*index    )%3)] -= ((index)%2)*incrementAmount;//clockwise
		
		frameCount++;
		if(frameCount%speed == 0){
			index++;
		}

		/*
		if(glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
			Model = glm::scale(Model, glm::vec3(1.1));
		}
		if(glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
			Model = glm::scale(Model, glm::vec3(0.9));
		}
		if(glfwGetKey( window, GLFW_KEY_Z ) == GLFW_PRESS){
			Model = glm::rotate(Model, 1.0f, glm::vec3(0.0f,0.0f,1.0f));
		}
		if(glfwGetKey( window, GLFW_KEY_X ) == GLFW_PRESS){
			Model = glm::translate(Model, glm::vec3(0.1f,0.0f,0.0f));
		}
		if(glfwGetKey( window, GLFW_KEY_Y ) == GLFW_PRESS){
			Model = glm::translate(Model, glm::vec3(0.0f,0.1f,0.0f));
		}
		*/
		if(glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS || glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){//go left
			//for(int i = 54; i < sizeof(g_center_vertex_buffer_data); i += 3){
			//	g_center_vertex_buffer_data[i] += -0.1;
			for(int i = 54; i < sizeof(g_vertex_buffer_data); i += 3){
				g_vertex_buffer_data[i] += -0.1;
			}
			cameraPos[0] += -0.1;
			cameraFocus[0] += -0.1;
			View = glm::lookAt(cameraPos,cameraFocus,cameraHead);
		}
		if(glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS || glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){//go right
			//for(int i = 54; i < sizeof(g_center_vertex_buffer_data); i += 3){
			//	g_center_vertex_buffer_data[i] += 0.1;
			for(int i = 54; i < sizeof(g_vertex_buffer_data); i += 3){
				g_vertex_buffer_data[i] += 0.1;
			}
			cameraPos[0] += 0.1;
			cameraFocus[0] += 0.1;
			View = glm::lookAt(cameraPos,cameraFocus,cameraHead);
		}
		if(glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS || glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){//go down
			//for(int i = 55; i < sizeof(g_center_vertex_buffer_data); i += 3){
			//	g_center_vertex_buffer_data[i] += -0.1;
			for(int i = 55; i < sizeof(g_vertex_buffer_data); i += 3){
				g_vertex_buffer_data[i] += -0.1;
			}
			cameraPos[1] += -0.1;
			cameraFocus[1] += -0.1;
			View = glm::lookAt(cameraPos,cameraFocus,cameraHead);
		}
		if(glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS || glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){//go up
			//for(int i = 55; i < sizeof(g_center_vertex_buffer_data); i += 3){
			//	g_center_vertex_buffer_data[i] += 0.1;
			for(int i = 55; i < sizeof(g_vertex_buffer_data); i += 3){
				g_vertex_buffer_data[i] += 0.1;
			}
			cameraPos[1] += 0.1;
			cameraFocus[1] += 0.1;
			View = glm::lookAt(cameraPos,cameraFocus,cameraHead);
		}



	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );


	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

