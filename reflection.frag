#version 330


out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform samplerCube cubemap;
uniform vec3 cameraPos;
uniform float fresnelBias;
uniform float fresnelPower;
uniform float fresnelScale;
vec3 diffuseColor = vec3(0.85, 0.44, 0.0);
//vec3 diffuseColor = vec3(1.0,1.0,1.0);
const vec3 lightDirection = normalize(vec3(0.2, -1.0, 0.3));
const float ambient = 0.8;

void main() 
{
	
	float brightness = max(dot(-lightDirection, normalize(Normal)), 0.0) + ambient;
	float ratio = 1.0/1.33;
	vec3 N = normalize(Normal);
	vec3 I = normalize(Position - cameraPos);
	vec3 refractVec = refract(I, N, ratio);
	vec3 reflectVec = reflect(I, N);
	
	float reflectionFactor = max(0.0, min(1.0, fresnelBias + fresnelScale * pow(1.0 + dot(I, N), fresnelPower)));
	//FragColor = vec4(mix(diffuseColor * brightness, texture(cubemap, reflectVec).rgb, 0.8), 1.0);
	//FragColor = vec4(mix(diffuseColor * brightness, texture(cubemap, refractVec).rgb, 0.8), 1.0);
	FragColor = vec4(mix(diffuseColor*brightness, mix(texture(cubemap, refractVec).rgb, texture(cubemap, reflectVec).rgb, reflectionFactor), 1.0), 1.0);
	//FragColor = vec4(mix(texture(cubemap, refractVec).rgb, texture(cubemap, reflectVec).rgb, reflectionFactor), 1.0);
}