#version 330 core

in vec3 vVertexPosition;
in vec3 vVertexNormal;
in vec2 vTexCoords;

uniform sampler2D uTexture;

out vec3 fFragColour;


void main()
{
	fFragColour = texture(uTexture, vTexCoords).xyz;
}