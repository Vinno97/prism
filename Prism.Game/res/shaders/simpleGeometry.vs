#version 420 core
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal; 
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj; 

out vec3 fragPos;
out vec3 normal;

void main() { 
	gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1 ); 
	fragPos = vec3(model * vec4(aPos.x, aPos.y, aPos.z, 1 ));
	vec3 Normal = mat3(transpose(inverse(model))) * aNormal;  
	normal = Normal;
}


