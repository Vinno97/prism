#version 330 core
out vec4 FragColor; 
uniform vec3 ambientLightColor;
uniform float ambientLightStrength;

uniform vec3 sunPosition;
uniform vec3 sunColor;

in vec3 fragPos;  
in vec3 normal;  

void main() {
    vec3 ambient = ambientLightStrength * ambientLightColor; 	
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(sunPosition - fragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * sunColor;
	vec3 result = (ambient + diffuse) * vec3(1.0, 1.0, 1.0);

    FragColor = vec4(result, 1.0);
}