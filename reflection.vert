#version 330

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;

out vec3 Position;
out vec3 Normal;

uniform mat4 model;
uniform mat4 mvp;

void main()
{
	Position = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	gl_Position = mvp * vec4(aPos, 1.0);
}