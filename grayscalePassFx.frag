#version 330

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D mainTex;

void main()
{
	FragColor = texture(mainTex, TexCoord);
	float average = (FragColor.r + FragColor.g + FragColor.b)/3.0;
	FragColor = vec4(average, average, average, 1.0);
}