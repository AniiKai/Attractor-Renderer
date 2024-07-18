#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/cglm.h>

#include "shader/shader.h"
#include "math/attractors.h"
#include "math/llist.h"
#include "misc/setup.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

int main() {

	// initial setup before window creation
	int n = setupWelcome();
	int fc = setupFS();
	int alg = setupAttr();
	int runTest = setupRT();
	setupConf();

	// initialize window variables
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	// create the window
	GLFWwindow* window; 
	if (fc == 0) {
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Att-R", glfwGetPrimaryMonitor(), NULL);
	} else {
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Att-R", NULL, NULL);
	}
	
	if (window == NULL) {
	    	printf("Failed to create GLFW window");
 	    	glfwTerminate();
	    	return -1;
	}
	
	// set the window as the current window 
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD");
		return -1;
       	}
	
	//Shader testShader("shader/defaultShader.vert", "shader/defaultShader.frag");
	unsigned int shader = createShader("shader/defaultShader.vert", "shader/defaultShader.frag");
	unsigned int texShader = createShader("shader/bloom.vert", "shader/bloom.frag");
	unsigned int blurShader = createShader("shader/blur.vert", "shader/blur.frag");
	
	// create buffer objects
	//unsigned int EBO;
	/*
	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	*/

	
	float quadVertices[] = { 
	//positions		//texCoords
	-1.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	-1.0f, -1.0f, 0.0f,	0.0f, 0.0f,

	
	-1.0f, -1.0f, 0.0f,	0.0f, 0.0f,
	1.0f, 1.0f, 0.0f,	1.0f, 1.0f,
	1.0f, -1.0f, 0.0f,	1.0f, 0.0f,
    	};

	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);

	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0); 

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		printf("FRAMEBUFFER NOT COMPLETE!\n");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	unsigned int pingpongFBO[2];
	unsigned int pingpongColorbuffers[2];
	glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongColorbuffers);
	for (int i=0; i<2; i++) {
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0); 
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			printf("FRAMEBUFFER NOT COMPLETE!\n");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
	}


	useShader(texShader);
	setInt(texShader, "scene", 0);
	setInt(texShader, "bloomBlur", 1);
	useShader(blurShader);
	setInt(blurShader, "image", 0);


	/*
	// create and assign the test obj to index 1 of the array buffer
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind current buffer 
	*/
	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);



	//testShader.use();
	useShader(shader);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_MULTISAMPLE);
	// attractor stuff here
	lNode** nodeArr = (lNode**)malloc(n * sizeof(lNode*)); // create list of nodes to simulate attractor with
	float x = 0.0001f;
	float y = 0.00015f;
	float z = 0.0002f;

	if (alg == 11) {
		x += 1.0f;
		z += 5.0f;
	}
	if (alg == 13) {
		x += 2.0f;
		z += 3.0f;
		y += 4.0f;
	}
	if (alg == 14) {
		x = -1.0f;
		y = 0;
		z = 0.5f;
	}
	for (int i=0; i<n; i++) {
		nodeArr[i] = newNode(x, y, z);
		x += 0.0002f;
		y += 0.00015f;
		z += 0.0001f;
		if (alg == 13) {
			x = 20*sin(i);
			y += 15*cos(i);
			z += 10*sin((float)i/2.0f);
		}
	}
	int div = 0;
	switch(alg) {
		case 1:
			div = 55;
			break;
		case 2:
			div = 15;	
			break;
		case 3:
			div = 2;
			break;
		case 4:
			div = 75;
			break;
		case 5:
			div = 20;
			break;
		case 6:
			div = 210;
			break;
		case 7:
			div = 5;
			break;
		case 8:
			div = 24;
			break;
		case 9:
			div = 2;
			break;
		case 10:
			div = 35;
			break;
		case 11:
			div = 14;
			break;
		case 12:
			div = 55;
			break;
		case 13:
			div = 55;
			break;
		case 14:
			div = 55;
			break;
		default:
			div = 55;
			break;
	}
	float max = 0;
	if (runTest == 0) {
		for (int i=0; i<100000; i++) {
			max = sizeTest(nodeArr, n, div, alg, max);
		}
	}

	mat4 model = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}};
			
	

	mat4 proj;
	glm_perspective_default(1920.0f/1080.0f, proj);
	vec3 up = {0.0f, 1.0f, 0.0f};
	mat4 view;

	srand(time(NULL));
	float camX = (float)(rand()%1000)/250.0f - 2.0f;
	float camY = (float)(rand()%1000)/250.0f - 2.0f;
	float camZ = (float)(rand()%1000)/250.0f - 2.0f;
	float pCamX = 1.0f;
	float pCamY = 1.0f;
	float pCamZ = 1.0f;
	int moveCounter = rand()%1000;

	double previousTime = glfwGetTime();
	int frames = 0;
	// openGL window loop
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		frames++;
		if (currentTime - previousTime >= 1.0) { // get simulation fps
			printf("fps: %d\n", frames);
			printf("max: %f\n", max); // comment this
			frames = 0;
			previousTime = currentTime;
		}

		processInput(window); // process user input
		
		pCamX += (camX - pCamX) * 0.005;
		pCamY += (camY - pCamY) * 0.005f;
		pCamZ += (camZ - pCamZ) * 0.005f;

		moveCounter -= 1;
		if (moveCounter <= 0) {
			moveCounter = rand()%1000;
			camX = (float)(rand()%1000)/250.0f - 2.0f;
			camY = (float)(rand()%1000)/250.0f - 2.0f;
			camZ = (float)(rand()%1000)/250.0f - 2.0f;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		useShader(shader);
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // background color 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glBindVertexArray(VAO);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind current buffer 
		

		vec3 eye = {pCamX, pCamY, pCamZ};
		vec3 center = {0.0f, 0.0f, 0.0f};
		glm_lookat(eye, center, up, view);

		setView(shader, "model", model);
		setView(shader, "view", view);
		setView(shader, "proj", proj);	
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // bind current buffer 

		if (runTest == 0) {
			visualizeTest(nodeArr[0], shader);
		} else {
			if (alg != 13) {
				runSim(nodeArr, n, div, shader, alg); // step the simulation
			} else {
				stepGravity(nodeArr, n, div, shader);
			}
		}
		glBindVertexArray(0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		bool horizontal = true;
		bool firstIt = true;
		int amount = 10;
		useShader(blurShader);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // background color 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i=0; i<amount; i++) {
			glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
			setInt(blurShader, "horizontal", horizontal);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, firstIt ? textureColorbuffer : pingpongColorbuffers[!horizontal]);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO); // bind current buffer 
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
			horizontal = !horizontal;
			if (firstIt) {
				firstIt = false;
			}
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);



		useShader(texShader);
		glDisable(GL_DEPTH_TEST);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // background color 
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO); // bind current buffer 
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);


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




