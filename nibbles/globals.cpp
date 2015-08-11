#define GLOBALS_CPP

#include <utility>

#include "globals.hpp"
#include "Nibbler.hpp"
#include "LightSource.hpp"
#include "EntityManager.hpp"

int initializeOGLstuff(){

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
	window = glfwCreateWindow( 1024, 768, "SPACE NIBBLES", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
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
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

    // Get a handle for our "MVP" uniform
    MatrixID = glGetUniformLocation(programID, "MVP");
    ViewMatrixID = glGetUniformLocation(programID, "V");
    ModelMatrixID = glGetUniformLocation(programID, "M");
    LightMatrixID = glGetUniformLocation(programID, "L");

    LightColorID = glGetUniformLocation(programID, "lightColor");

    // Get a handle for our buffers
    vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    vertexUVID = glGetAttribLocation(programID, "vertexUV");
    vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");

    // Load the texture
	Texture = loadBMP_custom("textures.bmp");

	// Get a handle for our "myTextureSampler" uniform
	TextureID  = glGetUniformLocation(programID, "myTextureSampler");

    // Get a handle for our "LightPosition" uniform
    LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

    OpacityID = glGetUniformLocation(programID, "opacity");
    
    b2Vec2 uniGravity(0,0);
    universe = new b2World(uniGravity);
	ContactListenerInstance = new EntityManager;
	universe->SetContactListener(ContactListenerInstance);

    meshes.insert(std::pair<std::string,Mesh>("nibblercore", Mesh("nibblercore.obj")));
    meshes.insert(std::pair<std::string,Mesh>("nibblercorona", Mesh("nibblercorona.obj")));
    meshes.insert(std::pair<std::string,Mesh>("debris1", Mesh("debris1.obj")));
    meshes.insert(std::pair<std::string,Mesh>("debris2", Mesh("debris2.obj")));
    meshes.insert(std::pair<std::string,Mesh>("debris3", Mesh("debris3.obj")));
    meshes.insert(std::pair<std::string,Mesh>("energycanister", Mesh("energycanister.obj")));
    meshes.insert(std::pair<std::string,Mesh>("coneship", Mesh("debris2.obj")));
    meshes.insert(std::pair<std::string,Mesh>("background", Mesh("background.obj")));

    player = new Nibbler(glm::vec3(0), glm::vec3(0,1,0), 0, glm::vec3(1));
    background = new Entity(glm::vec3(0,0,-10), glm::vec3(0,0,1), 0, glm::vec3(1));
    Part backgroundPart(*background, meshes["background"], glm::vec3(0), glm::vec3(0,0,1), 0, glm::vec3(1));
    theLight = new Entity(glm::vec3(0,0,10), glm::vec3(0,0,1), 0, glm::vec3(1));
    light = new LightSource(*light, meshes["nibblercore"], glm::vec3(0), glm::vec3(0,0,1), 0, glm::vec3(1), glm::vec3(0));

    return 0;
}

int floatSign(float val) {
    return (0 < val) - (val < 0);
}