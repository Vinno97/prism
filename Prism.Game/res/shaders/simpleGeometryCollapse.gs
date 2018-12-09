#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform float time;

float hash(vec2 co){
  float t = 12.9898*co.x + 78.233*co.y; 
  return t;
}

void main()
{
	float offset = hash(vec2(gl_in[0].gl_Position.x, gl_in[0].gl_Position.y))/10;
	float distance = time;
	
	if(time-offset <= 0) {
		offset = 0;
		distance = 0;
	}
	
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