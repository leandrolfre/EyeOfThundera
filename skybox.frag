#version 330

in vec3 TexCoord;
out vec4 FragColor;
uniform samplerCube cubemap;

void main() 
{
	FragColor = texture(cubemap, TexCoord);
}