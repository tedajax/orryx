#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

layout(std140) uniform CameraMatrices
{
	mat4 view;
	mat4 projection;
};

uniform mat4 model;

out vec3 vNormal;
out vec3 eyeDirection;

void main() {
	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(position, 1.0);
	vNormal = (model * vec4(normal, 0)).xyz;
	eyeDirection = vec3(0, 0, 0) - (view * model * vec4(position, 1)).xyz;
}