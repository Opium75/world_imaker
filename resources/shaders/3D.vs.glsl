#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aTexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vVertexPosition;
out vec3 vVertexNormal;
out vec2 vTexCoords;

void main()
{
	//passage en Vue
	vVertexPosition = vec3(uMVMatrix*vec4(aVertexPosition, 1.f)); 
	//idem pour les normales
	vVertexNormal = vec3(uNormalMatrix*vec4(aVertexNormal,0.f)); 
	vTexCoords = aTexCoords; //aucun changement
	gl_Position = uMVPMatrix*vec4(aVertexPosition, 1.f);
}