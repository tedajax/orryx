#version 330 core

out vec4 color;

vec3 lightDirection;
vec4 lightColor;
vec4 ambientColor;

in vec3 vNormal;
in vec3 eyeDirection;

void main() {
	lightDirection = vec3(0.5, 0.5, 0.0);
	lightColor = vec4(1.0, 1.0, 1.0, 1);
	ambientColor = vec4(0.2, 0.2, 0.2, 1);
	vec4 specularColor = vec4(1, 1, 1, 1);
	vec4 diffuse = vec4(1, 0, 0, 1);

	vec3 n = normalize(vNormal);
	vec3 l = normalize(lightDirection);
	float dirLight = clamp(dot(n, l), 0, 1);

	vec3 E = normalize(eyeDirection);
	vec3 R = reflect(-l, n);
	float specLight = clamp(dot(E, R), 0, 1);
	
	vec4 ambientLight = diffuse * ambientColor;
	vec4 diffuseLight = diffuse * lightColor * dirLight;
	vec4 specularLight = specularColor * lightColor * pow(specLight, 10);

	color = ambientLight + diffuseLight + specularLight;
}