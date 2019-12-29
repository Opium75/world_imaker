#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;


layout(std140) uniform bMatrices
{
	mat4 MVP;
	mat4 MV;
	mat4 Normal;
};


out vec3 vVertexPosition;
out vec3 vVertexNormal;
out vec3 vTexCoords;

void main()
{
	vVertexPosition = vec3(MV*vec4(aVertexPosition, 1.f));
	vVertexNormal = vec3(Normal*vec4(aVertexNormal,0.f));
	//Since we use Cube Maps, the texture coordinates are related to Position in object space centred on the origin.
	//BEWARE: since coordinates are different for cubemaps, it has to be flipped.
	vTexCoords = -aVertexPosition;
	gl_Position = MVP*vec4(aVertexPosition, 1.f);
}
