#include "shader.h"
#include <glad/glad.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int createShader(char* vertexPath, char* fragmentPath) {
	FILE* vFile;
	FILE* fFile;
	vFile = fopen(vertexPath, "r");
	fFile = fopen(fragmentPath, "r");
	char* vShader = (char*)calloc(1024, sizeof(char));
	char* fShader = (char*)calloc(1024, sizeof(char));
	char line[1024];
	while(fgets(line, sizeof(line), vFile) != NULL) {
		strcat(vShader, line);
	}
	while(fgets(line, sizeof(line), fFile) != NULL) {
		strcat(fShader, line);
	}
	fclose(vFile);
	fclose(fFile);

	unsigned int vertex; unsigned int fragment;
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, (const char**)&vShader, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, (const char**)&fShader, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	unsigned int ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);

	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	free(vShader);
	free(fShader);
	return ID;
}

void checkCompileErrors(GLuint shader, char* type) {
	GLint success;
	GLchar infoLog[1024];
	if (strcmp(type, "PROGRAM")) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			printf("%s\n%s\n", type, infoLog);
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			printf("%s\n%s\n", type, infoLog);
		}
	}
}

void setCols(unsigned int ID, char* name, float rgba[4]) {
			glUniform4f(glGetUniformLocation(ID, name), rgba[0], rgba[1], rgba[2], rgba[3]); // I didn't want to read documentation to figure out how to pass in the whole array at once so :] 
}

void setView(unsigned int ID, char* name, mat4 view) {
			glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &view[0][0]);
}

void useShader(unsigned int ID) {
	glUseProgram(ID);
}

