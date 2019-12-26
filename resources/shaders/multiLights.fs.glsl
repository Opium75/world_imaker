#version 430 core

in vec3 vVertexPosition;
in vec3 vVertexNormal;

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
	vec3 kD;
	vec3 kS;
	float shininess;
};
//material
layout(std140) uniform bMaterial
{
	MaterialData material;
};

layout(std140) uniform bAmbiantLight
{
	AmbiantLightData ambiant;
};


layout(std430, binding=0) buffer sPointLight
{
	PointLightData point[];
};

layout(std430, binding=1) buffer sDirectionLight
{
	DirectionLightData direction[];
};


vec3 ambiantLighting(const MaterialData material, const AmbiantLightData light)
{
	return material.colour*light.intensity;
}

vec3 bpDir(const MaterialData material, const DirectionLightData dLight, const vec3 position_vs, const vec3 normal_vs)
{
	vec3 halfVec = (dLight.direction_vs - position_vs)/2;
	vec3 fragColour = dLight.intensity*(
							material.kD*(dot(normalize(dLight.direction_vs), normalize(normal_vs)))
						  + material.kS*pow(dot(normalize(halfVec), normalize(normal_vs)), material.shininess)
	);
	return fragColour;
}

vec3 bpPoint(const MaterialData material, const PointLightData pLight, const vec3 position_vs, const vec3 normal_vs)
{
	vec3 wi = normalize(pLight.origin_vs - position_vs);
	vec3 li = pLight.intensity / pow(distance(position_vs, pLight.origin_vs),2);
	vec3 halfVec = (wi - position_vs)/2;
	vec3 fragColour = li*( material.kD*(dot(wi, normalize(normal_vs)))
						  + material.kS*pow(dot(normalize(halfVec), normalize(normal_vs)), material.shininess)

	);
	return fragColour;
}



void main()
{
	vec3 fragColour = material.colour;
	int nbPoint = point.length();
	int nbDir = direction.length();
	fragColour = ambiantLighting(material, ambiant);
	for( int i=0; i < nbPoint; ++i)
	{
		//fragColour += bpPoint(material, point[i], vVertexPosition, vVertexNormal);
	}
	//fragColour *= nbPoint;
	for( int i=0; i < nbDir; ++i)
	{
		//fragColour += bpDir(material, direction[i], vVertexPosition, vVertexNormal);
	}
	fFragColour = fragColour;
}