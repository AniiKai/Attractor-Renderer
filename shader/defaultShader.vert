#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 ourColor;
uniform vec4 ins;

void main() {
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f; // eh it works 
	float vel = sqrt(ins.x*ins.x + ins.y*ins.y + ins.z*ins.z);
	if (vel < 1.0f) { // map colors to speed
		r = 0.0f;
		g = vel;
		b = 1.0f;
	}
	else if (vel < 2.0f) {
		r = 0.0f;
		g = 1.0f;
		b = 2.0f - vel;
	}
	else if (vel < 3.0f) {
		r = vel - 2.0f;
		g = 1.0f;
		b = 0.0f;
	}
	else if (vel < 4.0f) {
		r = 1.0f;
		g = 4.0f - vel;
		b = 0.0f;	
	}
	else if (vel < 5.0f) {
		r = 1.0f;
		g = 0.0f;
		b = vel - 4.0f;
	}
	else {
		r = 1.0f;
		g = 0.0f;
		b = 1.0f;
	}
    gl_Position = vec4(aPos, 1.0);
    ourColor = vec4(r, g, b, ins.a);
}
