#version 430 core

in vec3 vVertexPosition;
in vec3 vVertexNormal;
in vec3 vTexCoords;

out vec3 fFragColour;

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
	vec3 baseColour, fragColour;
	baseColour =  vec3(1,1,1);
	fragColour = baseColour;
	fFragColour = fragColour;
}