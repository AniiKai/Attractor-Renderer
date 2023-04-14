#ifndef SHADER_H
#define SHADER_H

int createShader(char* vertexPath, char* fragmentPath);

void setCols(unsigned int ID, char* name, float rgba[4]);

void useShader(unsigned int ID);

#endif
