#version 330 core
out vec4 FragColor; 
uniform vec3 ambientLightColor;
uniform float ambientLightStrength;

in vec3 FragPos;  
vec3 lightPos = vec3(0.5, 1.0, 1.0);
vec3 lightColor = vec3(0.5, 1.0, 1.0);

void main() {
    vec3 ambient = ambientLightStrength * ambientLightColor; 	
	vec3 norm = normalize(FragPos);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse) * vec3(1.0, 1.0, 0.7);

    FragColor = vec4(result, 1.0);
}