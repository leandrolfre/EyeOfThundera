vec3 calculateAmbient(vec3 ambientLight) 
{
	return texture(material.diffuse0, TexCoord).rgb * ambientLight/*  * material.ka */;
}

vec3 calculateDiffuse(vec3 diffuseLight, vec3 normal, vec3 lightDir) 
{
	return max(dot(normal, lightDir), 0.0) * diffuseLight * texture(material.diffuse0, TexCoord).rgb/*  * material.kd */;
}

vec3 calculateSpecular(vec3 specularLight, vec3 normal, vec3 lightDir, vec3 viewDir) 
{
	vec3 reflectDir = reflect(-lightDir, normal);
	return pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * texture(material.specular0, TexCoord).rgb * specularLight/*  * material.ks */;
}