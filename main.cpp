// making this into a c file soon!
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader/shader.h"
#include "math/attractors.h"
#include "math/llist.h"

#include <iostream>
#include <stdlib.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

int main() {
	// initialize window variables
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// create the window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Attractors", NULL, NULL);
	
	if (window == NULL) {
	    	std::cout << "Failed to create GLFW window" << std::endl;
 	    	glfwTerminate();
	    	return -1;
	}
	
	// set the window as the current window 
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
       	}
	
	Shader testShader("shader/defaultShader.vert", "shader/defaultShader.frag");
	
	
	// create buffer objects
	//unsigned int EBO;
	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	
	// create and assign the test obj to index 1 of the array buffer
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind current buffer 

	testShader.use();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// attractor stuff here
	
	int n = 1000; // ammount of nodes to simulate
	lNode** nodeArr = (lNode**)malloc(n * sizeof(lNode*)); // create list of nodes to simulate attractor with
	float x = 0.0001f;
	float y = 0.00015f;
	float z = 0.0002f;
	for (int i=0; i<n; i++) {
		nodeArr[i] = newNode(x, y, z);
		x += 0.0002f;
		y += 0.00015f;
		z += 0.0001f;
	}


	// openGL window loop
	while (!glfwWindowShouldClose(window)) {

		processInput(window); // process user input

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // background color 
		glClear(GL_COLOR_BUFFER_BIT);
		
		testShader.use(); // use the test obj shader 
		
		stepLorenz(nodeArr, n, 50); // step the simulation

		// swap render buffer 
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	for (int i=0; i<n; i++) {
		delNode(nodeArr[i]);
	}
	free(nodeArr);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow *window) {
	// close the program if you press the escape key 
    	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// set the buffer size 
	glViewport(0, 0, width, height);

}




