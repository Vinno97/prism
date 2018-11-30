#version 420 core

in vec2 UV;
out vec4 color;

uniform vec3 ambientLightColor;
uniform float ambientLightStrength;
uniform vec3 sunPosition;
uniform vec3 sunColor;

uniform mat4 view;
uniform mat4 proj;

struct Light {
    vec3 Position;
    vec3 Color;
};

uniform vec3 lightPosition;
uniform vec3 lightColor;

layout(binding = 0) uniform sampler2D gPosition;
layout(binding = 1) uniform sampler2D gNormal;
layout(binding = 2) uniform sampler2D gAlbedo;
layout(binding = 3) uniform sampler2D gDepth;

vec3 decodeLocation()
{
  vec4 clipSpaceLocation;
  clipSpaceLocation.xy = UV * 2.0f - 1.0f;
  clipSpaceLocation.z = texture(gDepth, UV).r * 2.0f - 1.0f;;
  clipSpaceLocation.w = 1.0f;
  vec4 homogenousLocation = (inverse(proj) * inverse(view)) * clipSpaceLocation;
  return homogenousLocation.xyz / homogenousLocation.w;
}

float CalcLinearZ(float depth) {
    const float zFar = 100.0;
    const float zNear = 0.1;

    // bias it from [0, 1] to [-1, 1]
    float linear = zNear / (zFar - depth * (zFar - zNear)) * zFar;

    return (linear * 2.0) - 1.0;
}

vec3 WorldPosFromDepth(float depth) {
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(UV * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = inverse(proj) * clipSpacePosition;

    // Perspective division
    viewSpacePosition /= viewSpacePosition.w;

    vec4 worldSpacePosition = inverse(view) * viewSpacePosition;

    return worldSpacePosition.xyz;
}

vec3 depth(){
    float v = pow(texture(gDepth, UV).r , 256);
	return vec3(v,v,v);
}

void main() {
    vec3 FragPos = texture(gPosition, UV).rgb;
    vec3 Normal = texture(gNormal, UV).rgb;
    vec3 Albedo = texture(gAlbedo, UV).rgb;
	vec3 Depth = texture(gDepth, UV).rgb;
	
	vec3 loc = WorldPosFromDepth(Depth.x);
	
	vec3 ambient = ambientLightStrength * ambientLightColor; 	
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(sunPosition - loc);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * sunColor;
				
	float distance = length(lightPosition - loc);
	float attenuation = 1.0 / (1.0 + 0.7 * distance + 
    		    1.8 * (distance * distance));    
					
	vec3 surfaceToLight = lightPosition - loc;
	float brightness = max(dot(normalize(surfaceToLight), surfaceToLight), 0.0); (length(surfaceToLight) * length(norm));
	
	//diffuse.x += attenuation;

	
	diffuse.x *= brightness;
	ambient.x *= brightness;
	
	vec3 result = (ambient + (diffuse)) * vec3(Albedo);
	
	color = vec4(result, 1.0);

}
