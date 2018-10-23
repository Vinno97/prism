#version 330 core
out vec4 FragColor; 
uniform vec3 ambientLightColor;
uniform float ambientLightStrength;
void main() {
    vec3 ambient = ambientLightStrength * ambientLightColor; 
	vec3 result = ambient * vec3(.1f, .1f, .1f);
    FragColor = vec4(result, 1.0);
}