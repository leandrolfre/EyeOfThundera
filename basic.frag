#version 330 core

#define NR_POINT_LIGHTS 1

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
	vec3 ka;
	vec3 kd;
	vec3 ks;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	float cutOff;
	float outerCutOff;
	float kc;
	float kl;
	float kq;
};

struct PointLight {
    vec3 position;
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	float kc;
	float kl;
	float kq;
};

struct DirLight {
	vec3 direction;
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;
uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;
uniform vec3 cameraPos;

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

out vec4 FragColor;

vec3 calculateAmbient(vec3 ambientLight, vec3 diffuseMap);
vec3 calculateDiffuse(vec3 diffuseLight, vec3 normal, vec3 lightDir, vec3 diffuseMap);
vec3 calculateSpecular(vec3 specularLight, vec3 normal, vec3 lightDir, vec3 viewDir, vec3 specularMap, float shininess);

vec3 calculateDirectionalLight(DirLight light, vec3 normal, vec3 viewDir) 
{
	vec3  ambient = calculateAmbient(light.ambient, texture(material.diffuse, TexCoord).rgb);
	vec3 lightDir = normalize(-light.direction);
	vec3 diffuse = calculateDiffuse(light.diffuse, normal, lightDir, texture(material.diffuse, TexCoord).rgb);
	vec3 specular = calculateSpecular(light.specular, normal, lightDir, viewDir, texture(material.specular, TexCoord).rgb, material.shininess);

	return (ambient + diffuse + specular);
}

float calculateAttenuation(float kc, float kl, float kq, float distance) 
{
	return 1.0 / (kc + kl * distance + kq * (distance * distance));
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	
	vec3 lightDir = light.position - fragPos;
	float distance = length(lightDir);
	lightDir = normalize(lightDir);
	float attenuation = calculateAttenuation(light.kc, light.kl, light.kq, distance);

	vec3  ambient = calculateAmbient(light.ambient, texture(material.diffuse, TexCoord).rgb);
	vec3 diffuse = calculateDiffuse(light.diffuse, normal, lightDir, texture(material.diffuse, TexCoord).rgb);
	vec3 specular = calculateSpecular(light.specular, normal, lightDir, viewDir, texture(material.specular, TexCoord).rgb, material.shininess);

	ambient*= attenuation;
	diffuse*= attenuation;
	specular*= attenuation;

	return (ambient + diffuse + specular);
}

vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	
	vec3 lightDir = light.position - fragPos;
	float distance = length(lightDir);
	lightDir = normalize(lightDir);

	float theta = dot(lightDir, normalize(-light.direction));
	float intensity = smoothstep(light.outerCutOff, light.cutOff, theta);
	
	vec3  ambient = calculateAmbient(light.ambient, texture(material.diffuse, TexCoord).rgb);
	vec3 diffuse = calculateDiffuse(light.diffuse, normal, lightDir, texture(material.diffuse, TexCoord).rgb);
	vec3 specular = calculateSpecular(light.specular, normal, lightDir, viewDir, texture(material.specular, TexCoord).rgb, material.shininess);

	float attenuation = calculateAttenuation(light.kc, light.kl, light.kq, distance);
	ambient*= attenuation;
	diffuse*= attenuation;
	specular*= attenuation;
	
	diffuse*=intensity;
	specular*=intensity;
	return (ambient + diffuse + specular);
}

void main()
{	
	//if (texture(material.diffuse, TexCoord).a < 0.01) discard;
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 finalColor = vec3(0.0); 
	finalColor += calculateDirectionalLight(dirLight, normal, viewDir);

	// for(int i = 0; i < NR_POINT_LIGHTS; i++) 
	// {
	// 	finalColor+= calculatePointLight(pointLight[i], normal, FragPos, viewDir); 
	// }

	//finalColor += calculateSpotLight(spotLight, normal, FragPos, viewDir);

    FragColor = vec4(finalColor, 1.0);
}
