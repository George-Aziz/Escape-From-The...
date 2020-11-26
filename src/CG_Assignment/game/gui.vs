#version 330 core

in vec2 pos;

out vec2 TexCoords;

uniform mat4 tMatrix;

void main(void){

	gl_Position = vec4(pos, 0.0, 1.0);
	TexCoords = vec2((pos.x + 1.0) / 2.0, 1 - (pos.y + 1.0) / 2.0);
}