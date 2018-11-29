#version 420 core

in vec2 UV;
out vec4 color;

uniform vec3 ambientLightColor;
uniform float ambientLightStrength;
uniform vec3 sunPosition;
uniform vec3 sunColor;

uniform mat4 view;

struct Light {
    vec3 Position;
    vec3 Color;
};

uniform vec3 lightPosition;
uniform vec3 lightColor;

layout(binding = 0) uniform sampler2D gPosition;
layout(binding = 1) uniform sampler2D gNormal;
layout(binding = 2) uniform sampler2D gAlbedo;

void main(){

    vec3 FragPos = texture(gPosition, UV).rgb;
    vec3 Normal = texture(gNormal, UV).rgb;
    vec3 Albedo = texture(gAlbedo, UV).rgb;
	
	vec3 ambient = ambientLightStrength * ambientLightColor; 	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(sunPosition - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * sunColor;
	
	vec4 testpos1 = inverse(view) * vec4(-42, 1, -15, 1.0);
	vec3 testpos = testpos1.xyz;
	
	vec3 lightDirPoint = normalize(testpos.xyz - FragPos);
	vec3 diffuseLight = max(dot(Normal, lightDirPoint), 0.0) * Albedo * vec3(3, 3, 0);
	
	float test = length(testpos.xyz - FragPos);
	diffuse += (test/100);
	vec3 result = (ambient + (diffuse)) * vec3(Albedo);
	color = vec4(FragPos);
}
