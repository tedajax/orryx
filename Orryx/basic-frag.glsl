#version 330 core

out vec4 color;

varying vec3 vPos;

void main() {
	color = vec4(vPos.x, vPos.y, vPos.z, 1);
}