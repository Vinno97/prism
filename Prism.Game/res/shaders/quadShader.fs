#version 420 core

in vec2 UV;
out vec4 color;

uniform mat4 view;
uniform mat4 proj;

struct DirectionalLight {
    vec3 Direction;
    vec3 Color;
	float AmbientIntensity;
    float DiffuseIntensity;
};

struct PointLight {
	vec3 Position;
    vec3 Color;
	float AmbientIntensity;
    float DiffuseIntensity;
	
	float Constant;
	float Linear;
	float Exp;
};

uniform DirectionalLight gDirectionalLight;

layout(binding = 0) uniform sampler2D gPosition;
layout(binding = 1) uniform sampler2D gNormal;
layout(binding = 2) uniform sampler2D gAlbedo;
layout(binding = 3) uniform sampler2D gDepth;

vec3 WorldPosFromDepth(float depth) {
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(UV * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = inverse(proj) * clipSpacePosition;

    // Perspective division
    viewSpacePosition /= viewSpacePosition.w;

    vec4 worldSpacePosition = inverse(view) * viewSpacePosition;

    return worldSpacePosition.xyz;
}

void main() {
    vec3 FragPos = texture(gPosition, UV).rgb;
    vec3 Normal = texture(gNormal, UV).rgb;
    vec3 Albedo = texture(gAlbedo, UV).rgb;
	vec3 Depth = texture(gDepth, UV).rgb;
	vec3 worldPos = WorldPosFromDepth(Depth.x);
	
	vec4 AmbientColor = vec4(gDirectionalLight.Color * gDirectionalLight.AmbientIntensity, 1.0f);
	float DiffuseFactor = dot(normalize(Normal), -gDirectionalLight.Direction);
	
	vec4 DiffuseColor;
	
	if (DiffuseFactor > 0) {
        DiffuseColor = vec4(gDirectionalLight.Color * gDirectionalLight.DiffuseIntensity * DiffuseFactor, 1.0f);
    }
    else {
        DiffuseColor = vec4(0, 0, 0, 0);
    }
	color = vec4(Albedo, 1) * (AmbientColor + DiffuseColor);
}

