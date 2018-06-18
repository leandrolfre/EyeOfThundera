#version 330

layout(location=0) in vec3 aPos;

out vec3 TexCoord;

uniform mat4 vp;

void main() 
{
	TexCoord = aPos;
	vec4 position = vp * vec4(aPos, 1.0);
	gl_Position = position.xyww;
}