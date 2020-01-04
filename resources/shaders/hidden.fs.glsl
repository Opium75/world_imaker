#version 430 core

in vec3 vVertexPosition;

//This time, we only care about selection
layout(location = 1) out uvec4 fCubeIndex;

uniform uvec3 uCubeIndex;

struct AmbiantLightData
{
	vec3 intensity;
};

struct PointLightData
{
	vec3 intensity;
	vec3 origin_vs;
};

struct DirectionLightData
{
	vec3 intensity;
	vec3 direction_vs;
};

struct MaterialData
{
	vec3 colour;
	bool isTextured;
	vec3 kD;
	vec3 kS;
	float shininess;
};

layout(std140) uniform bMaterial
{
	MaterialData material;
};


uniform	samplerCube uBaseTexture;

layout(std140) uniform bAmbiantLight
{
	AmbiantLightData ambiant;
};

layout(std430) buffer sPointLight
{
	PointLightData point[];
};

layout(std430) buffer sDirectionLight
{
	DirectionLightData direction[];
};

layout(std430) buffer sLightNumber
{
	int nbPoints;
	int nbDirs;
};
//No lighting

void main()
{
	//using the distance of the fragment to the camera as test
	float fragDepth = gl_FragCoord.z;
	//adding whether the fragment belongs to a cube as alpha parameter. -> 1 == true
	bool isInCube = fragDepth > 0.0f;
	fCubeIndex = uvec4(uCubeIndex, uint(isInCube));
}