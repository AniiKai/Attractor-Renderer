#ifndef SHADER_H
#define SHADER_H
#include <cglm/cglm.h>
#include <glad/glad.h>
int createShader(char* vertexPath, char* fragmentPath);

void setCols(unsigned int ID, char* name, float rgba[4]);

void checkCompileErrors(GLuint shader, char* type);

void setView(unsigned int ID, char* name, mat4 view);
void useShader(unsigned int ID);

void setInt(unsigned int ID, char* name, int val);

#endif
