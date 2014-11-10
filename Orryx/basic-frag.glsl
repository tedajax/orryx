#version 330 core

out vec4 color;

varying vec4 vPos;

void main() {
	vec4 col1 = vec4(0, 0, 0, 1);
	vec4 col2 = vec4(1, 1, 0, 1);
	float heightFactor = 2;
	color = mix(col1, col2, (vPos.y + heightFactor) / (heightFactor * 2));
}