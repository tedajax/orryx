#version 330

layout(location = 0) in vec3 position;

layout(std140) uniform CameraMatrices
{
	mat4 view;
	mat4 projection;
};

uniform mat4 model;

varying vec4 vPos;

void main() {
	vPos = model * vec4(position, 1.0);
	gl_Position = projection * view * model * vec4(position, 1.0);
}