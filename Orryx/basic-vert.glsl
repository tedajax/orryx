in vec3 position;

varying vec4 vPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	vPos = model * vec4(position, 1.0);
	gl_Position = projection * view * model * vec4(position, 1.0);
}