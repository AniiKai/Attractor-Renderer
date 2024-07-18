#version 330 core
layout (location = 0) out vec4 FragColor;

in vec4 ourColor;

void main() {
	vec4 outColor = vec4(ourColor.xyz * ourColor.w, 1.0);
    	FragColor = outColor;
}
