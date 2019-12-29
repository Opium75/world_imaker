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

vec3 ambiantLighting(const vec3 baseColour, const AmbiantLightData light)
{
	return baseColour*light.intensity;
}

vec3 blinnPhong(const vec3 Li, const vec3 wo, const vec3 wi, const vec3 N, const vec3 Kd, const vec3 Ks, const float shininess)
{
	vec3 halfVec = normalize(wi + wo);
	return Li*(Kd*max((dot(wi, N)),0) + Ks*pow(max(dot(halfVec,N),0), shininess));
}
vec3 bpDir(const vec3 baseColour, const MaterialData material, const DirectionLightData dLight , const vec3 position_vs, const vec3 normal_vs)
{
	vec3 lightDir_vs = dLight.direction_vs;
	//
    vec3 li = dLight.intensity.rgb;
	vec3 wo = normalize(-position_vs);
	vec3 wi = normalize(lightDir_vs);
	vec3 N = normalize(normal_vs);
	return baseColour*blinnPhong(li, wo, wi, N, material.kD, material.kS, material.shininess);
}

vec3 bpPoint(const vec3 baseColour, const MaterialData material, const PointLightData pLight, const vec3 position_vs, const vec3 normal_vs)
{
	vec3 lightPos_vs = pLight.origin_vs;
	float d = distance(position_vs, lightPos_vs);
	//
	vec3 li = pLight.intensity.rgb / d*d;
	vec3 wo = normalize(position_vs);
	vec3 wi = normalize(lightPos_vs - position_vs);
	vec3 N = normalize(normal_vs);
	return baseColour*blinnPhong(li, wo, wi, N, material.kD, material.kS, material.shininess);
}



void main()
{
	vec3 baseColour, fragColour, temp;
	if( material.isTextured )
		baseColour = texture(uBaseTexture, vTexCoords).rgb;
    else
	{
		baseColour = material.colour;
	}
	fragColour = ambiantLighting(baseColour, ambiant);
	for( int i=0; i < nbPoints; ++i)
	{
		temp = bpPoint(baseColour, material, point[i], vVertexPosition, vVertexNormal);
		fragColour = fragColour + temp;
	}
	for( int i=0; i < nbDirs; ++i)
	{
		temp = bpDir(baseColour, material, direction[i], vVertexPosition, vVertexNormal);
		fragColour = fragColour + temp;
	}
	fFragColour = fragColour;
}