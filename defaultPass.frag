#version 330

in vec2 TexCoord;
out vec4 FragColor;
uniform sampler2D mainTex;

void main() 
{
	FragColor = vec4(texture(mainTex, TexCoord).rgb, 1.0);
}
