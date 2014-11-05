in vec3 position;

varying vec3 vPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	vPos = position;
	gl_Position = projection * view * model * vec4(position, 1.0);
}