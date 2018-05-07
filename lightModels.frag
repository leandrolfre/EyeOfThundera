vec3 calculateAmbient(vec3 ambientLight, vec3 diffuseMap) 
{
	return diffuseMap * ambientLight/*  * material.ka */;
}

vec3 calculateDiffuse(vec3 diffuseLight, vec3 normal, vec3 lightDir, vec3 diffuseMap) 
{
	return max(dot(normal, lightDir), 0.0) * diffuseLight * diffuseMap/*  * material.kd */;
}

vec3 calculateSpecular(vec3 specularLight, vec3 normal, vec3 lightDir, vec3 viewDir, vec3 specularMap, float shininess) 
{
	vec3 reflectDir = reflect(-lightDir, normal);
	return pow(max(dot(viewDir, reflectDir), 0.0), shininess) * specularMap * specularLight/*  * material.ks */;
}