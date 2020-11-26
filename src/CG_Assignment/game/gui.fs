#version 330 core

in vec2 TexCoords;

out vec4 ourColor;

uniform sampler2D guiTex;

void main(void){

	ourColor = texture(guiTex,TexCoords);
}