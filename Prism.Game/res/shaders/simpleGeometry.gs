#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform float time;
uniform int isAnimating;

in VS
{
    vec3 fragPos;
	vec3 normal;
} source[]; //One for each input vertex, but since we're using points, it's just one.

out FS
{
    vec3 fragPos;
	vec3 normal;
} dest;

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 5.0;
    vec3 direction = normal * time * magnitude; 
    return position + vec4(direction, 0.0);
} 

vec3 GetNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
} 

void main()
{
	dest.normal = source[0].normal;
	dest.fragPos = source[0].fragPos;

	if(isAnimating == 1) {
		vec3 normal = GetNormal();

		gl_Position = explode(gl_in[0].gl_Position, normal);
		EmitVertex();
		gl_Position = explode(gl_in[1].gl_Position, normal);
		EmitVertex();
		gl_Position = explode(gl_in[2].gl_Position, normal);
		EmitVertex();
		EndPrimitive();
	} else {
		gl_Position = gl_in[0].gl_Position;
		EmitVertex();
		gl_Position = gl_in[1].gl_Position;
		EmitVertex();
		gl_Position = gl_in[2].gl_Position;
		EmitVertex();
		EndPrimitive();
	}
} 