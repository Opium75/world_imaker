#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
//layout(location = 3) in vec3 aTexCoords;


layout(std140) uniform bMatrices
{
	mat4 MVP;
	mat4 MV;
	mat4 Normal;
};


out vec3 vVertexPosition;
out vec3 vVertexNormal;
//out vec3 vTexCoords;

void main()
{
	//passage en Vue
	vVertexPosition = vec3(MV*vec4(aVertexPosition, 1.f));
	//idem pour les normales
	vVertexNormal = vec3(Normal*vec4(aVertexNormal,0.f));
	//vTexCoords = aTexCoords; //aucun changement
	gl_Position = MVP*vec4(aVertexPosition, 1.f);
}
