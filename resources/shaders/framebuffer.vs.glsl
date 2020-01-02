#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 2) in vec2 aTexCoords;


layout(std140) uniform bMatrices
{
	mat4 MVP;
	mat4 MV;
	mat4 Normal;
};


out vec2 vTexCoords;

void main()
{
	vTexCoords = vec2(aTexCoords.x, aTexCoords.y);
	gl_Position = vec4(aVertexPosition, 0.f, 1.f);
}
