#version 420 core

in vec2 UV;
out vec4 color;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 shadowView;
uniform mat4 shadowProj;

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

vec2 poissonDisk[4] = vec2[](
  vec2( -0.94201624, -0.39906216 ),
  vec2( 0.94558609, -0.76890725 ),
  vec2( -0.094184101, -0.92938870 ),
  vec2( 0.34495938, 0.29387760 )
);

uniform vec2 kernel[9] = vec2[]
(
   vec2(0.95581, -0.18159), vec2(0.50147, -0.35807), vec2(0.69607, 0.35559),
   vec2(-0.003682, -0.5915), vec2(0.1593, 0.08975), vec2(-0.6503, 0.05818),
   vec2(0.11915, 0.78449), vec2(-0.34296, 0.51575), vec2(-0.6038, -0.41527)
);


uniform DirectionalLight gDirectionalLight;
uniform PointLight gPointLights[100];
uniform float numPointLights;

layout(binding = 0) uniform sampler2D gPosition;
layout(binding = 1) uniform sampler2D gNormal;
layout(binding = 2) uniform sampler2D gAlbedo;
layout(binding = 3) uniform sampler2D gDepth;
layout(binding = 4) uniform sampler2D gShadowMap;

float CalcShadowFactor(vec4 LightSpacePos)
{
    vec3 ProjCoords = LightSpacePos.xyz / LightSpacePos.w;
    vec2 UVCoords;
    UVCoords.x = 0.5 * ProjCoords.x + 0.5;
    UVCoords.y = 0.5 * ProjCoords.y + 0.5;
    float z = 0.5 * ProjCoords.z + 0.5;
    float Depth = texture(gShadowMap, UVCoords).x;
    if (Depth < (z + 0.00001))
        return 0.5;
    else
        return 1.0;
}

vec4 WorldPosFromDepth(float depth, mat4 camera) {
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(UV * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = inverse(proj) * clipSpacePosition;

    // Perspective division
    viewSpacePosition /= viewSpacePosition.w;

    vec4 worldSpacePosition = inverse(camera) * viewSpacePosition;

    return worldSpacePosition;
}

float LinearizeDepth(in vec2 uv, float depth)
{
    float zNear = 0.5; 
    float zFar  = 7.5;
    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

vec3 calcPointLight(vec3 normal, vec3 worldPos, PointLight pointLight) {
	vec3 ambientColor = pointLight.Color * pointLight.AmbientIntensity;
	float diffuse = dot(normal, -pointLight.Position);
	float distance = length(pointLight.Position-worldPos);

	
	float Attenuation = gPointLights[0].Constant + pointLight.Linear * distance + pointLight.Exp * distance * distance;
	return pointLight.Color/Attenuation;
}

void main() {
    vec3 FragPos = texture(gPosition, UV).rgb;
    vec3 Normal = texture(gNormal, UV).rgb;
    vec3 Albedo = texture(gAlbedo, UV).rgb;
	vec3 Depth = texture(gDepth, UV).rgb;
	
	vec3 worldPos = WorldPosFromDepth(Depth.x, view).xyz;
	
	vec4 shadowPos = shadowProj * shadowView * vec4(worldPos, 1.0);
	vec3 shadowCoordTemp = shadowPos.xyz / shadowPos.w;
	
	shadowCoordTemp = shadowCoordTemp * 0.5 + 0.5; 
	vec4 shadowCoord = vec4(shadowCoordTemp, 1.0);
	
	float bias = 0.005;
	float t1 = texture(gShadowMap, shadowCoord.xy).r;
	float t2 = shadowCoord.z-bias;
	
	float shadow = 0;

// Poisson sampling
	float visibility = 1;
	for (int i=0;i<8;i++){
		int index = int(16.0*random(worldPos.xyy, i))%16;
		if ( texture( gShadowMap, shadowCoord.xy + poissonDisk[i]/700.0 ).r  <  shadowCoord.z-bias ){
			visibility -= 0.1;
		}
	}
	
	vec4 AmbientColor = vec4(gDirectionalLight.Color * gDirectionalLight.AmbientIntensity, 1.0f);
	float DiffuseFactor = dot(normalize(Normal), -gDirectionalLight.Direction);
	
	vec4 DiffuseColor;
	
	if (DiffuseFactor > 0) {
        DiffuseColor = vec4(gDirectionalLight.Color * gDirectionalLight.DiffuseIntensity * DiffuseFactor, 1.0f);
    }
    else {
        DiffuseColor = vec4(0, 0, 0, 0);
    }
	
	
	
	color = vec4(Albedo, 1) * (AmbientColor  + pointColor + DiffuseColor);
	//float t = LinearizeDepth(UV, texture(gShadowMap, UV).r);
	//color = vec4(t, t, t, 1.0);
	//color = pointColor;
}

