#version 430 core

in vec3 vVertexPosition;
in vec3 vVertexNormal;
in vec3 vFragColour;

out vec3 fFragColour;

struct AmbiantLightData
{
	vec3 colour;
	float intensity;
};

struct PointLightData
{
	vec3 colour;
	vec3 origin_vs;
	float intensity;
};

struct DirLightData
{
	vec3 colour;
	vec3 direction_vs;
	float intensity;
};

uniform sampler2D uTexture;
uniform AmbiantLightData uAmbiantLight;


//material
layout(std140) uniform bMaterial
{
	vec3 colour;
	vec3 kD;
	vec3 kS;
	float shininess;
};

layout(std140) uniform bAmbiantLight
{
	AmbiantLightData ambiant;
};


layout(std430, binding=0) buffer PointLights
{
	PointLightData pointData[];
};

layout(std430, binding=1) buffer DirLightsData
{
	DirLightData dirData[];
};

vec3 blinnPhongDir(vec3 kd, vec3 ks, float shiny, vec3 lightDir_vs, vec3 lightIntensity, vec3 position_vs, vec3 normal_vs)
{
	vec3 halfVector = (-position_vs+lightDir_vs)/2;
	vec3 fragColour = lightIntensity*(
		kd*(dot(normalize(lightDir_vs), normalize(normal_vs)) )
		+ ks*pow( dot(normalize(halfVector), normalize(normal_vs)),shiny)
		);
	return fragColour;
}

vec3 blinnPhongPoint(vec3 kd, vec3 ks, float shiny, vec3 lightPos_vs, vec3 lightIntensity, vec3 position_vs, vec3 normal_vs)
{
	vec3 wi = normalize(lightPos_vs - position_vs);
	vec3 li  = lightIntensity / pow(distance(position_vs, lightPos_vs),2);
	vec3 halfVector = (-position_vs + wi)/2;
	vec3 fragColour = li*(
		kd*(dot(wi, normalize(normal_vs)) )
		+ ks*pow( dot(normalize(halfVector), normalize(normal_vs)),shiny)
		);
	return fragColour;
}

void main()
{
	vec3 fragColour = vFragColour;
	//adding ambiant light
	fragColour *= ambiant.colour*ambiant.intensity;
	fFragColour = fragColour;
}