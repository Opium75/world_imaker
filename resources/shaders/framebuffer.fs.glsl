#version 430 core

in vec2 vTexCoords;

//sending colour to Framebuffer
layout(location = 0)out vec3 fFragColour;

uniform sampler2D uFramebuffer;

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

void main()
{
	fFragColour = texture(uFramebuffer, vTexCoords).rgb;
}
