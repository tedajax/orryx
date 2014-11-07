#version 330 core

out vec4 color;

varying vec4 vPos;

void main() {
	vec4 col1 = vec4(0.6, 0, 0, 1);
	vec4 col2 = vec4(1, 0.4, 0, 1);
	color = mix(col1, col2, (vPos.y + 1) / 2);
}