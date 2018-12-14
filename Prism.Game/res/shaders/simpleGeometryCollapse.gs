#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

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

uniform float time;
uniform int isAnimating;

float hash(vec2 co){
  float t = 12.9898*co.x + 78.233*co.y; 
  return t;
}

void main()
{
	float offset = hash(vec2(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y))/10;
	float distance = time;
	
	if(time-offset <= 0 || isAnimating == 0) {
		offset = 0;
		distance = 0;
	}
	
	dest.normal = source[0].normal;
	dest.fragPos = source[0].fragPos;
	
    gl_Position = gl_in[0].gl_Position;
	gl_Position.y += distance-offset;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	gl_Position.y += distance-offset;
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	gl_Position.y += distance-offset;
    EmitVertex();
    EndPrimitive();
} 