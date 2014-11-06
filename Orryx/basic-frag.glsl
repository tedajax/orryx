#version 330 core

out vec4 color;

varying vec4 vPos;

void main() {
	vec4 red = vec4(1, 0, 0, 1);
	vec4 blue = vec4(0, 0, 1, 1);
	color = mix(red, blue, (vPos.y + 1) / 2);
}